#pragma once
#include "uDisplayObject.h"
#include "uRenderer.h"
#include <vector>
#include <iostream>
namespace utl
{
	typedef uResource<SDL_Surface, uResourceManager::loadImage, SDL_FreeSurface>::Handle uImage;
	class uSDLRenderObject : public uDisplayObject
	{
		friend class uRendererSDL;
	public:
		uSDLRenderObject() : uDisplayObject() {}
		uSDLRenderObject(std::string resName) : uDisplayObject(resName), srcImage(_resName) {
			_target->setWH(getImage()->w, getImage()->h);
		}
		inline void setDefaultWH()
		{
			_target->setWH(getImage()->w, getImage()->h);
		}
		inline int getTexture() { return _texture; }
		inline void setImage(std::string&& path)
		{
			srcImage.set(std::forward<std::string>(path));
			uDisplayManager::reloadObject(static_cast<uDisplayObject*>(this));
		}
		inline SDL_Surface* getImage()
		{
			return srcImage.get();
		}
	private:
		int _texture;
		uImage srcImage;
	};
	class uRendererSDL : public uRenderer
	{
	public:
		typedef  uSDLRenderObject RenderObject;
		

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
			//access by SDL_Surface
			_textures.push_back(SDL_CreateTextureFromSurface(_renderer, image));
			return _textures.size() - 1;
			//make entry trough SDL_surface and get new int
		}
		virtual void destroyTexture(int texId)
		{
			SDL_DestroyTexture(_textures.at(texId));
		}
		virtual void drawObject(uDisplayObject* object)
		{
			auto renderObject = static_cast<RenderObject*>(object);

			//put coordinate point in the middle of bounding box
			SDL_Rect temp{ renderObject->getTarget()->x, renderObject->getTarget()->y, renderObject->getTarget()->w , renderObject->getTarget()->h };
			if (SDL_RenderCopy(_renderer, _textures.at(renderObject->getTexture()), NULL, &temp) == -1)//access by int
				std::cout << SDL_GetError();
		}
		virtual void loadObject(uDisplayObject* object)
		{
			static_cast<RenderObject*>(object)->_texture = loadTexture(static_cast<RenderObject*>(object)->getImage());
		}
		virtual void reloadObject(uDisplayObject* object)
		{
			destroyObject(object);
			loadObject(object);
		}
		virtual void destroyObject(uDisplayObject* object)
		{
			destroyTexture(static_cast<RenderObject*>(object)->_texture);
		}
		virtual void showScr()
		{
			SDL_RenderPresent(_renderer);
		}
		virtual void clearScr()
		{
			SDL_RenderClear(_renderer);
		}
		virtual ~uRendererSDL()
		{
			for (auto i : _textures)
				SDL_DestroyTexture(i);
			SDL_DestroyRenderer(_renderer);
		}
		bool valid=false;
	private:
		SDL_Renderer* _renderer;
		std::vector<SDL_Texture*> _textures;
		//TODO: replace vector with map
	};
};