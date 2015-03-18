#include "JetServer.hpp"
#include "network/Packet.hpp"
#include "network/ClientType.hpp"
#include <GFK/System/Logger.hpp>
#include <bitset>

using namespace jetGame;

JetServer::JetServer() :
ConsoleGame(true, 60),
networkCounter(0),
networkSendsPerSecond(20),
updateCounter(0),
playerIdCounter(0),
netHelper(NetworkHelper::ConnectionType::Server)
{

}

JetServer::~JetServer()
{

}

void JetServer::Initialize()
{
	gfk::ConsoleGame::Initialize();

	netHelper.StartServer(55777);
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, clientData, gameTime);
		}
	);

	// Run net discovery on port 55778, inform clients that port 55777 is what the server is using
	netDiscoveryServer.Start(55778, 55777);
}

void JetServer::LoadContent()
{
	gfk::ConsoleGame::LoadContent();
}

void JetServer::UnloadContent()
{
	gfk::ConsoleGame::UnloadContent();
}

void JetServer::PrintServerInfo()
{
	std::cout << std::endl << "There are " << netHelper.GetPlayerCount() << "/" << netHelper.GetMaxPlayerCount() << " players" << std::endl;
	netHelper.ForEachClient([](const ClientData &client)
		{
			std::cout << "Client " << client.id << ": client type is " << static_cast<unsigned int>(client.clientType) << std::endl;
		}
	);

	std::cout << std::endl;
}

void JetServer::Update(const gfk::GameTime &gameTime)
{
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToPlayers(gameTime);
	updateCounter++;
}

void JetServer::UpdateNetwork(const gfk::GameTime &gameTime)
{
	netDiscoveryServer.RespondToDiscoveryRequests();
	netHelper.Receive(gameTime);
}

void JetServer::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
{
	if (protocol == Packet::NEW_DESKTOP_CLIENT_REQ || protocol == Packet::NEW_ANDROID_CLIENT_REQ)
	{
		clientData.id = playerIdCounter;
		playerIdCounter++;
		clientData.jet.Reset();

		if (protocol == Packet::NEW_DESKTOP_CLIENT_REQ)
		{
			clientData.clientType = ClientType::DESKTOP;
			Logger::Logf("New desktop user connected. ID is: %d\n", clientData.id);
			netHelper.WritePacket(NewDesktopClientPacketRes(clientData.id), true);
		}
		else if (protocol == Packet::NEW_ANDROID_CLIENT_REQ)
		{
			clientData.clientType = ClientType::GFK_ANDROID;
			Logger::Logf("New Android user connected. ID is: %d\n", clientData.id);
			netHelper.WritePacket(NewAndroidClientPacketRes(clientData.id), true);
		}

		// Inform the new users of the existing clients
		netHelper.ForEachClient([this, &clientData](const ClientData &otherPlayer)
			{
				if (otherPlayer.id == clientData.id)
				{
					return;
				}

				if (otherPlayer.clientType == ClientType::DESKTOP)
				{
					clientData.outbox.WritePacket(NewDesktopClientPacketRes(otherPlayer.id), true);
				}
				else if (otherPlayer.clientType == ClientType::GFK_ANDROID)
				{
					clientData.outbox.WritePacket(NewAndroidClientPacketRes(otherPlayer.id), true);
				}
			}
		);

		// Inform the client of its ID
		clientData.outbox.WritePacket(ClientIdPacketRes(clientData.id), true);

		PrintServerInfo();
	}
	else if (protocol == Packet::GAME_INPUT_REQ)
	{
		GameInput input = GameInputPacketReq::ReadFromBuffer(netBuffer).input;
		clientData.jet.Update(input, gameTime);

		// TODO - validate input sequence number
		if (input.sequenceNumber > clientData.lastInputSequenceNumber)
		{
			clientData.lastInputSequenceNumber = input.sequenceNumber;
		}
	}
	else if (protocol == Packet::DISCONNECT_REQ)
	{
		Logger::Logf("User %hu wants to disconnect\n", clientData.id);
		netHelper.WritePacket(DisconnectPacketRes(clientData.id), true);

		PrintServerInfo();
	}
}

void JetServer::UpdateGame(const gfk::GameTime &gameTime)
{

}

void JetServer::SendStateToPlayers(const gfk::GameTime &gameTime)
{
	int iterCutoff = targetUpdateFramesPerSecond / networkSendsPerSecond;

	if (networkCounter >= iterCutoff)
	{
		netHelper.ForEachClient([this](const ClientData &clientData)
			{
				// Write jet data for all clients
				netHelper.WritePacket(JetInputPacketRes(clientData.id, clientData.jet.GetPosition(), clientData.jet.GetRotation(), clientData.jet.GetEngineRPM(), clientData.lastInputSequenceNumber), false);
			}
		);

		netHelper.Send();

		networkCounter = 1;
	}
	else
	{
		networkCounter++;
	}
}

int main()
{
	JetServer server;
	server.Run();

	return 0;
}
