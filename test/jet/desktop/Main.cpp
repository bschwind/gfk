#include <string>
#include <iostream>
#include <GFK/Game.hpp>
#include "JetGame.hpp"

using namespace jetGame;

int main()
{
	JetGame game("Jet", 1280, 720);
	game.Run();
	return 0;
}
