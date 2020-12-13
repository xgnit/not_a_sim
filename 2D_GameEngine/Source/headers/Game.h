#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SDL_SmartPointer.h"

#include "GameObject.h"

class Game
{
public:
	Game() = default;
	~Game();

	void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen = false);
	void handle_events();
	void update();
	void render();
	void clean();
	void run();

	bool running() { return is_running; }
private:
	bool is_running;
	SDL_SmartWindow window;
	SDL_SmartRenderer renderer;
	int cnt = 0;

	std::shared_ptr<GameObject> obj;

	// 60 is the fps
	static const int frame_delay = 1000/60;


};

