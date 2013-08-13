#include <string>
#include <iostream>
#include <GFK/Game.hpp>
#include <GFK/Network/UDPSocket.hpp>

using namespace gfk;

class ClientGame : public gfk::Game
{
public:
	ClientGame() : Game(true) {}

	UDPSocket socket;
	static const int length = 256;

	void LoadContent()
	{
		socket.Open(55778);
	}

	void Update(const GameTime &gameTime)
	{
		std::string message;
		std::getline(std::cin, message);
		char *sendBuffer = (char*)message.c_str();

		socket.Send(IPAddress(127,0,0,1,55777), sendBuffer, length);
	}
};

int main()
{
	ClientGame game;
	game.Run();
	return 0;
}
