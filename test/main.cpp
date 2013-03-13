#include <string>
#include <iostream>
#include <GFK/Game.hpp>

int main()
{
	gfk::Game game("Test Game", 1280, 720);
	game.Run();
}
