#pragma once

#include "Game.h"
#include "SDL_SmartPointer.h"

class TextureManager
{

public:
	static SDL_Texture* load_texture(std::string texture, SDL_Renderer* re);

};