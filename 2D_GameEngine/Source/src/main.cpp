
#include <SDL.h>
#include "Game.h"



int main(int argc, char *argv[])
{
	
	std::unique_ptr<Game> game = std::make_unique<Game>();
	game->init("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->run();


	return 1;
}