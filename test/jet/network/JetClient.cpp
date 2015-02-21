#include "network/JetClient.hpp"
#include "network/Packet.hpp"
#include <GFK/System/Logger.hpp>
#include <chrono>
#include <thread>

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

		if (players.find(playerId) != players.end())
		{
			ClientData &player = players[playerId];

			player.jet.SetPosition(Vector3(jetX, jetY, jetZ));
			player.jet.SetRotation(Quaternion(jetRX, jetRY, jetRZ, jetRW));
		}
	}
	else if (protocol == Packet::NEW_DESKTOP_CLIENT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Desktop user joined with id %hu\n", playerId);
		players[playerId] = ClientData();
	}
	else if (protocol == Packet::NEW_ANDROID_CLIENT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Android user joined with id %hu\n", playerId);
		players[playerId] = ClientData();
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

}
