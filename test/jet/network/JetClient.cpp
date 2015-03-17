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
netHelper(NetworkHelper::ConnectionType::Client),
localPlayerId(0)
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
		netHelper.WritePacket(NewDesktopClientPacketReq());
	}
	else if (clientType == ClientType::GFK_ANDROID)
	{
		netHelper.WritePacket(NewAndroidClientPacketReq());
	}

	netHelper.Send();
}

void JetClient::DisconnectFromServer()
{
	netHelper.WritePacket(DisconnectPacketReq());
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

void JetClient::WritePacket(const Packet &packet)
{
	netHelper.WritePacket(packet);
}

void JetClient::SendOutgoingPackets()
{
	netHelper.Send();
}

void JetClient::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
{
	receivedNewInput = false;
	if (protocol == Packet::JET_INPUT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		float jetX = netBuffer.ReadFloat32();
		float jetY = netBuffer.ReadFloat32();
		float jetZ = netBuffer.ReadFloat32();

		float jetRX = netBuffer.ReadFloat32();
		float jetRY = netBuffer.ReadFloat32();
		float jetRZ = netBuffer.ReadFloat32();
		float jetRW = netBuffer.ReadFloat32();

		float engineRPM = netBuffer.ReadFloat32();

		unsigned int lastInputSequenceNumber = netBuffer.ReadUnsignedInt32();

		if (players.find(playerId) != players.end())
		{
			ClientData *player = &players[playerId];

			if (lastInputSequenceNumber > player->lastInputSequenceNumber)
			{
				// If this is a remote player
				if (localPlayerId != playerId)
				{
					player->lastJet = player->displayJet;
					player->currentSmoothing = 0.0f;

					player->jet.SetPosition(Vector3(jetX, jetY, jetZ));
					player->jet.SetRotation(Quaternion(jetRX, jetRY, jetRZ, jetRW));
					player->jet.SetEngineRPM(engineRPM);
					player->lastInputSequenceNumber = lastInputSequenceNumber;
				}
				else
				{
					player->jet.SetPosition(Vector3(jetX, jetY, jetZ));
					player->jet.SetRotation(Quaternion(jetRX, jetRY, jetRZ, jetRW));
					player->jet.SetEngineRPM(engineRPM);
					player->lastInputSequenceNumber = lastInputSequenceNumber;
				}

				receivedNewInput = true;
			}
		}
	}
	else if (protocol == Packet::NEW_DESKTOP_CLIENT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Desktop user joined with id %hu\n", playerId);
		players[playerId] = ClientData();
		players[playerId].id = playerId;
	}
	else if (protocol == Packet::NEW_ANDROID_CLIENT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Android user joined with id %hu\n", playerId);
		players[playerId] = ClientData();
		players[playerId].id = playerId;
	}
	else if (protocol == Packet::CLIENT_ID_RES)
	{
		localPlayerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Got ID from server: %hu\n", localPlayerId);
	}
	else if (protocol == Packet::DISCONNECT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Player %hu disconnected\n", playerId);
		players.erase(playerId);
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

}
