#pragma once

#include "SDL_SmartPointer.h"
#include <string>


class GameObject
{
public:
	GameObject(std::string texture_sheet, SDL_SmartRenderer ren)
	{
		renderer = ren;
		tex = SDL_SmartPointer::create_texture(texture_sheet, ren);
	}
	~GameObject() = default;

	void update()
	{
		xpos = 0;
		ypos = 0;
		src_rect->h = 32;
		src_rect->w = 32;
		src_rect->x = 0;
		src_rect->y = 0;

		dest_rect->w = src_rect->w * 2;
		dest_rect->h = src_rect->h * 2;
		dest_rect->x = xpos;
		dest_rect->y = ypos;
	}
	void render()
	{
		SDL_Smart::sdl_rendercopy(renderer, tex, NULL, dest_rect);
	};

private:
	int xpos = 0;
	int ypos = 0;

	SDL_SmartTexture tex{nullptr};
	std::unique_ptr<SDL_Rect> src_rect{ std::make_unique<SDL_Rect>() };
	std::unique_ptr<SDL_Rect> dest_rect{ std::make_unique<SDL_Rect>() };
	SDL_SmartRenderer renderer{nullptr};


};

