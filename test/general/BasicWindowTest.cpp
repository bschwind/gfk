#include <string>
#include <iostream>
#include <GFK/Game.hpp>

using namespace gfk;

int main()
{
	Game game("Basic Window Test", 1280, 720);
	game.Run();
	return 0;
}
