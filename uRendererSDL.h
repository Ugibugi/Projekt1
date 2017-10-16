#pragma once
#include "uDisplayObject.h"
#include "uRenderer.h"
#include <vector>
#include <iostream>
namespace utl
{
	class uRendererSDL : public uRenderer
	{
	public:
		uRendererSDL(SDL_Window* window, int index, uint32_t flags)
		{
			_renderer = SDL_CreateRenderer(window, index, flags);
			if (_renderer != nullptr)
			{
				valid = true;
			}

		}
		virtual int loadTexture(SDL_Surface* image)
		{
			//TODO: replace vector with map
			_textures.push_back(SDL_CreateTextureFromSurface(_renderer, image));
			return _textures.size() - 1;
		}
		virtual void destroyTexture(int texId)
		{
			SDL_DestroyTexture(_textures.at(texId));
		}
		virtual void drawObject(uDisplayObject* object)
		{
		
				if (SDL_RenderCopy(_renderer, _textures.at(object->getTexture()), NULL, object->getTarget()) == -1)
					std::cout << SDL_GetError();
		}
		virtual void showScr()
		{
			SDL_RenderPresent(_renderer);
		}
		virtual void clearScr()
		{
			SDL_RenderClear(_renderer);
		}
		~uRendererSDL()
		{
			for (auto i : _textures)
				SDL_DestroyTexture(i);
			SDL_DestroyRenderer(_renderer);
		}
		bool valid=false;
	private:
		SDL_Renderer* _renderer;
		std::vector<SDL_Texture*> _textures;
	};
};