#include "network/JetClient.hpp"
#include "network/Packet.hpp"
#include <GFK/System/Logger.hpp>
#include <chrono>
#include <thread>

#include <iostream>

using namespace gfk;

namespace jetGame
{

JetClient::JetClient() :
localPlayerId(0),
netHelper(NetworkHelper::ConnectionType::Client)
{

}

JetClient::~JetClient()
{

}

void JetClient::ConnectToServer(const std::string &hostName, unsigned short port, unsigned char clientType)
{
	netHelper.ConnectToServer(hostName, port);
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, clientData, gameTime);
		}
	);

	if (clientType == ClientType::DESKTOP)
	{
		netHelper.WritePacket(NewDesktopClientPacketReq(), true);
	}
	else if (clientType == ClientType::GFK_ANDROID)
	{
		netHelper.WritePacket(NewAndroidClientPacketReq(), true);
	}

	netHelper.Send();
}

void JetClient::DisconnectFromServer()
{
	netHelper.WritePacket(DisconnectPacketReq(), true);
	netHelper.Send();

	// HACK: Give the disconnect packet time to reach the server
	// before cutting off the connection. Get a more graceful solution later.
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	netHelper.DisconnectFromServer();
}

void JetClient::ProcessIncomingPackets(const gfk::GameTime &gameTime)
{
	netHelper.Receive(gameTime);
}

void JetClient::WritePacket(const Packet &packet, bool reliable)
{
	netHelper.WritePacket(packet, reliable);
}

void JetClient::SendOutgoingPackets()
{
	netHelper.Send();
}

void JetClient::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
{
	if (protocol == Packet::JET_INPUT_RES)
	{
		JetInputPacketRes jetStatePacket = JetInputPacketRes::ReadFromBuffer(netBuffer);

		if (players.find(jetStatePacket.playerID) != players.end())
		{
			ClientData &player = players[jetStatePacket.playerID];

			if (jetStatePacket.lastInputSequenceNumber > player.lastInputSequenceNumber)
			{
				// If this is a remote player, update the smoothing variables
				if (localPlayerId != jetStatePacket.playerID)
				{
					player.lastJet = player.displayJet;
					player.currentSmoothing = 0.0f;
				}
				else
				{
					receivedNewInput = true;
				}

				player.jet.SetPosition(jetStatePacket.position);
				player.jet.SetRotation(jetStatePacket.rotation);
				player.jet.SetEngineRPM(jetStatePacket.engineRPM);
				player.lastInputSequenceNumber = jetStatePacket.lastInputSequenceNumber;
			}
		}
	}
	else if (protocol == Packet::NEW_DESKTOP_CLIENT_RES)
	{
		NewDesktopClientPacketRes packet = NewDesktopClientPacketRes::ReadFromBuffer(netBuffer);
		Logger::Logf("Desktop user joined with id %hu\n", packet.id);
		players[packet.id] = ClientData();
		players[packet.id].id = packet.id;
		players[packet.id].clientType = ClientType::DESKTOP;

		PrintGameInfo();
	}
	else if (protocol == Packet::NEW_ANDROID_CLIENT_RES)
	{
		NewAndroidClientPacketRes packet = NewAndroidClientPacketRes::ReadFromBuffer(netBuffer);
		Logger::Logf("Android user joined with id %hu\n", packet.id);
		players[packet.id] = ClientData();
		players[packet.id].id = packet.id;
		players[packet.id].clientType = ClientType::GFK_ANDROID;

		PrintGameInfo();
	}
	else if (protocol == Packet::CLIENT_ID_RES)
	{
		ClientIdPacketRes packet = ClientIdPacketRes::ReadFromBuffer(netBuffer);
		localPlayerId = packet.id;
		Logger::Logf("My ID from the server: %hu\n", packet.id);
	}
	else if (protocol == Packet::DISCONNECT_RES)
	{
		DisconnectPacketRes packet = DisconnectPacketRes::ReadFromBuffer(netBuffer);
		Logger::Logf("Player %hu disconnected\n", packet.id);
		players.erase(packet.id);

		PrintGameInfo();
	}
}

void JetClient::Update(const gfk::GameTime &gameTime)
{
	for (auto &player : players)
	{
		// Only update remote players
		if (localPlayerId != player.second.id)
		{
			// TODO - count the number of frames between state updates
			//        to find the actual number here, instead of just 15.0f
			float increment = 1.0f / 15.0f;
			player.second.currentSmoothing += increment;

			if (player.second.currentSmoothing > 1.0f)
			{
				// For now, prevent "extrapolation"
				player.second.currentSmoothing = 1.0f;
			}

			Vector3 lerpedPos = Vector3::Lerp(player.second.lastJet.GetPosition(), player.second.jet.GetPosition(), player.second.currentSmoothing);
			player.second.displayJet.SetPosition(lerpedPos);

			Quaternion lerpedRot = Quaternion::Slerp(player.second.lastJet.GetRotation(), player.second.jet.GetRotation(), player.second.currentSmoothing);
			player.second.displayJet.SetRotation(lerpedRot);
		}
	}
}

ClientData* JetClient::GetLocalClient()
{
	if (players.find(localPlayerId) != players.end())
	{
		return &players[localPlayerId];
	}
	else
	{
		return nullptr;
	}
}

void JetClient::PrintGameInfo()
{
	Logger::Logf("\nThere are %d/%d players\n", players.size(), 32);
	for (const auto &player : players)
	{
		Logger::Logf("Client %hu: client type is %d\n", player.second.id, static_cast<unsigned int>(player.second.clientType));
	}

	Logger::Log("\n");
}

}
