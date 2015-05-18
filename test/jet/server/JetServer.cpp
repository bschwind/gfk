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
	netHelper.RegisterMappingHandler([this]()
					 {
						 HandlePortMappingChange();
					 }
		);
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, clientData, gameTime);
		}
	);

	// Run net discovery on port 55778, inform clients that port 55777 is what the server is using
	netDiscoveryServer.Start(55778, 55777);
	PrintServerInfo();
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
	if (netHelper.IsPortMappingActive())
	{
		IPAddress address = netHelper.GetPublicIPAddress();
		std::cout << "Port mapped, clients should connect to "
			  << address.GetIPV4String() << ":"
			  << address.GetPort() << std::endl;
	}
	else if (netHelper.HasPortMappingError())
	{
		std::cout << "Port mapping error: "
			  << netHelper.GetPortMappingError() << std::endl;
	}
	else
	{
		std::cout << "Port mapping in progress" << std::endl;
	}

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
			netHelper.WritePacket(NewDesktopClientRes(clientData.id), true);
		}
		else if (protocol == Packet::NEW_ANDROID_CLIENT_REQ)
		{
			clientData.clientType = ClientType::GFK_ANDROID;
			Logger::Logf("New Android user connected. ID is: %d\n", clientData.id);
			netHelper.WritePacket(NewAndroidClientRes(clientData.id), true);
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
					clientData.outbox.WritePacket(NewDesktopClientRes(otherPlayer.id), true);
				}
				else if (otherPlayer.clientType == ClientType::GFK_ANDROID)
				{
					clientData.outbox.WritePacket(NewAndroidClientRes(otherPlayer.id), true);
				}
			}
		);

		// Inform the client of its ID
		clientData.outbox.WritePacket(ClientIdRes(clientData.id), true);

		PrintServerInfo();
	}
	else if (protocol == Packet::GAME_INPUT_REQ)
	{
		GameInput input;

		GameInputReq req = GameInputReq::ReadFromBuffer(netBuffer);
		input.sequenceNumber = req.sequenceNumber;
		input.mouseDiffX = req.mouseX;
		input.mouseDiffY = req.mouseY;
		input.keyW = req.keyW;
		input.keyS = req.keyS;
		input.keyA = req.keyA;
		input.keyD = req.keyD;
		input.keyLeftShift = req.keyLeftShift;

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
		netHelper.WritePacket(DisconnectRes(clientData.id), true);

		PrintServerInfo();
	}
}

void JetServer::HandlePortMappingChange() {
	PrintServerInfo();
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
				netHelper.WritePacket(JetInputRes(clientData.id,
					clientData.jet.GetPosition(),
					clientData.jet.GetRotation(),
					clientData.jet.GetEngineRPM(),
					clientData.jet.GetRollVel(),
					clientData.jet.GetPitchVel(),
					clientData.jet.GetYawVel(),
					clientData.lastInputSequenceNumber), false);
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
