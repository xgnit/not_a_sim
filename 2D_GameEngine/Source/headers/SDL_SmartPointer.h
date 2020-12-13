#pragma once
#include <SDL.h>


struct sdl_deleter
{
	void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

using std::unique_ptr;
using SDL_SmartWindow = unique_ptr<SDL_Window, sdl_deleter>;
using SDL_SmartRenderer = std::shared_ptr<SDL_Renderer>;
using SDL_SmartTexture = unique_ptr<SDL_Texture, sdl_deleter>;

struct SDL_SmartPointer 
{
public:
	static SDL_SmartWindow
		create_window(char const *title, int x, int y, int w, int h, Uint32 flags)
	{
		return unique_ptr<SDL_Window, sdl_deleter>(
			SDL_CreateWindow(title, x, y, w, h, flags),
			sdl_deleter());
	}
	
	static SDL_SmartTexture
		create_texture(std::string pic, std::shared_ptr<SDL_Renderer> renderer)
	{
		SDL_Surface* tmp_surf = IMG_Load(pic.c_str());
		auto tex = SDL_SmartTexture(
			SDL_CreateTextureFromSurface(renderer.get(), tmp_surf),
			sdl_deleter());
		SDL_FreeSurface(tmp_surf);
		return tex;
	}

	static SDL_SmartRenderer
		create_renderer(unique_ptr<SDL_Window, sdl_deleter>&window)
	{
		return SDL_SmartRenderer(
			SDL_CreateRenderer(window.get(), -1, 0),
			sdl_deleter());
	}
};


struct SDL_Smart
{
	static void sdl_renderclear(SDL_SmartRenderer& renderer)
	{
		SDL_RenderClear(renderer.get());
	}

	static void sdl_rendercopy(SDL_SmartRenderer& renderer, SDL_SmartTexture& tex, unique_ptr<SDL_Rect>& src, unique_ptr<SDL_Rect>& dest)
	{
		SDL_RenderCopy(renderer.get(), tex.get(), src.get(), dest.get());
	}

	static void sdl_rendercopy(SDL_SmartRenderer& renderer, SDL_SmartTexture& tex, std::nullptr_t src, unique_ptr<SDL_Rect>& dest)
	{
		SDL_RenderCopy(renderer.get(), tex.get(), NULL, dest.get());
	}

	static void sdl_rendercopy(SDL_SmartRenderer& renderer, SDL_SmartTexture& tex, unique_ptr<SDL_Rect>& src, std::nullptr_t dest)
	{
		SDL_RenderCopy(renderer.get(), tex.get(), src.get(), NULL);
	}

	static void sdl_renderpresent(SDL_SmartRenderer& renderer)
	{
		SDL_RenderPresent(renderer.get());
	}
};