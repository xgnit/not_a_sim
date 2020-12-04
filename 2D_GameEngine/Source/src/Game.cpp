#include "Game.h"
#include <iostream>
#include <windows.h>

using std::endl;
using std::cout;
using std::unique_ptr;

SDL_SmartTexture playertex;

unique_ptr<SDL_Rect> src_rect = NULL;
unique_ptr<SDL_Rect> dest_rect = std::make_unique<SDL_Rect>();

Game::~Game()
{
	clean();
}

void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (0 == SDL_Init(SDL_INIT_EVERYTHING))
	{
		cout << "Subsystem initialized" << endl;
		window = SDL_SmartPointer::create_window(title.c_str(), xpos, ypos, height, width, flags);
		if (window)
		{
			cout << "window created!" << endl;
		}
		renderer = SDL_SmartPointer::create_renderer(window);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}
		is_running = true;
	}
	else
	{
		is_running = false;
	}
	playertex = SDL_SmartPointer::create_texture("Assets/player.png", renderer);
}

void Game::handle_events()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	dest_rect->h = 64;
	dest_rect->w = 64;
	//dest_rect.x += 1;
	//dest_rect.y += 1;

	++cnt;
	cout << cnt << endl;

}

void Game::render()
{
	SDL_Smart::sdl_renderclear(renderer);
	SDL_Smart::sdl_rendercopy(renderer, playertex, NULL, dest_rect);
	SDL_Smart::sdl_renderpresent(renderer);

}

void Game::clean()
{
	SDL_Quit();
	cout << "game terminated" << endl;
}

void Game::run()
{
	while (running())
	{
		auto frame_start = SDL_GetTicks();
		
		handle_events();
		update();
		render();

		auto frame_time = SDL_GetTicks() - frame_start;
		if (frame_time > frame_delay)
		{
			SDL_Delay(frame_delay - frame_time);
		}
	}
}
