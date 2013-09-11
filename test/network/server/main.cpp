#include <string>
#include <iostream>
#include <GFK/Game.hpp>
#include <GFK/Network/UDPSocket.hpp>

using namespace gfk;

class ServerGame : public gfk::Game
{
public:
	ServerGame() : Game(true) {}

	UDPSocket socket;
	unsigned char receiveBuffer[256];

	void LoadContent()
	{
		socket.Open(55777);
	}

	void Update(const GameTime &gameTime)
	{
		IPAddress sender;
		int byteReadCount = socket.Receive(sender, receiveBuffer, sizeof(receiveBuffer));
		if (!byteReadCount)
		{
			return;
		}

		std::cout << receiveBuffer << std::endl;
	}
};

int main()
{
	ServerGame game;
	game.Run();
	return 0;
}
