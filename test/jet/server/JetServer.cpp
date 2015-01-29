#include "JetServer.hpp"
#include "network/Packet.hpp"
#include <GFK/System/Logger.hpp>
#include <bitset>

using namespace jetGame;

JetServer::JetServer() :
ConsoleGame(true, 120),
networkCounter(0),
networkSendsPerSecond(20),
updateCounter(0),
netHelper(NetworkHelper::ConnectionType::Server),
jet(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0))
{

}

JetServer::~JetServer()
{

}

void JetServer::Initialize()
{
	gfk::ConsoleGame::Initialize();

	netHelper.StartServer(55777);
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, gameTime);
		}
	);
}

void JetServer::LoadContent()
{
	gfk::ConsoleGame::LoadContent();
}

void JetServer::UnloadContent()
{
	gfk::ConsoleGame::UnloadContent();
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
	netHelper.Receive(gameTime);
}

void JetServer::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, const gfk::GameTime &gameTime)
{
	if (protocol == Packet::NEW_DESKTOP_CLIENT_REQ)
	{
		Logger::Log("Desktop user connected\n");
	}
	else if (protocol == Packet::NEW_ANDROID_CLIENT_REQ)
	{
		Logger::Log("Android user connected\n");
	}
	else if (protocol == Packet::JET_INPUT_REQ)
	{
		float throttleAmt = netBuffer.ReadFloat32();
		float rollInput = netBuffer.ReadFloat32();
		float pitchInput = netBuffer.ReadFloat32();
		float yawInput = netBuffer.ReadFloat32();
		float thrusterEnabled = netBuffer.ReadUnsignedByte();

		jet.Update(throttleAmt, rollInput, pitchInput, yawInput, thrusterEnabled == 1, gameTime);

		// buffer.WriteFloat32(throttleAmt);
		// buffer.WriteFloat32(rollInput);
		// buffer.WriteFloat32(pitchInput);
		// buffer.WriteFloat32(yawInput);
		// buffer.WriteUnsignedByte(thrusterEnabled);
	}
	else if (protocol == Packet::DISCONNECT_REQ)
	{
		// sender is in the list of connections
		Logger::Log("Someone wants to disconnect\n");
	}
}

void JetServer::UpdateGame(const gfk::GameTime &gameTime)
{
	jet.Update(0, 0, 0, 0, false, gameTime);
}

void JetServer::SendStateToPlayers(const gfk::GameTime &gameTime)
{
	int iterCutoff = targetUpdateFramesPerSecond / networkSendsPerSecond;

	if (networkCounter >= iterCutoff)
	{
		netHelper.WritePacket(JetInputPacketRes(jet.GetPosition().X, jet.GetPosition().Y, jet.GetPosition().Z));
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
