#include "TextureManager.h"


SDL_Texture* TextureManager::load_texture(std::string texture, SDL_Renderer * re)
{
	
	SDL_Surface* tmp_surf = IMG_Load(texture.c_str());
	auto tex = SDL_CreateTextureFromSurface(re, tmp_surf);
	SDL_FreeSurface(tmp_surf);

	return tex;
}
