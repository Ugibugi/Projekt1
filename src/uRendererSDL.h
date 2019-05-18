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
		uSDLRenderObject() noexcept : uDisplayObject() {}
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
			uDisplayManager::reloadObject(this);
		}
		inline void setImage(std::string& path)
		{
			srcImage.set(path);
			uDisplayManager::reloadObject(this);
		}
		inline SDL_Surface* getImage()
		{
			return srcImage.get();
		}
	private:
		int _texture;
		uImage srcImage;
	};
	struct uRendererSDLTextureEntry
	{
		SDL_Texture* tex;
		SDL_Surface* surf;
		uint32_t ref_count;
	};
	class uRendererSDL : public uRenderer
	{
	public:
		typedef uSDLRenderObject			RenderObject;
		typedef	uRendererSDLTextureEntry	TextureEntry;

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
			if (_surfIndexes.count(image) > 0)
			{
				_textures.at(_surfIndexes.at(image)).ref_count++;
				return _surfIndexes.at(image);
			}
			else
			{
				_textures.push_back({ SDL_CreateTextureFromSurface(_renderer, image), image, 1});
				_surfIndexes[image] = _textures.size() - 1;
				return _textures.size() - 1;
			}
			
			//make entry trough SDL_surface and get new int
		}
		virtual void destroyTexture(int texId)
		{
			_textures.at(texId).ref_count--;
			if (_textures.at(texId).ref_count == 0)
			{
				SDL_DestroyTexture(_textures.at(texId).tex);
				_surfIndexes.erase(_textures.at(texId).surf);
			}
		}
		virtual void drawObject(uDisplayObject* object)
		{
			auto renderObject = dynamic_cast<RenderObject*>(object);

			//put coordinate point in the middle of bounding box
			SDL_Rect temp{ renderObject->getTarget()->x, renderObject->getTarget()->y, renderObject->getTarget()->w , renderObject->getTarget()->h };
			if (SDL_RenderCopy(_renderer, _textures.at(renderObject->getTexture()).tex, NULL, &temp) == -1)//access by int
				std::cout << __FILE__ << " : "<<__LINE__ <<  "[Error]: "<<  SDL_GetError() << '\n';
		}
		virtual void loadObject(uDisplayObject* object)
		{
			dynamic_cast<RenderObject*>(object)->_texture = loadTexture(dynamic_cast<RenderObject*>(object)->getImage());
		}
		virtual void reloadObject(uDisplayObject* object)
		{
			destroyObject(object);
			loadObject(object);
		}
		virtual void destroyObject(uDisplayObject* object)
		{
			destroyTexture(dynamic_cast<RenderObject*>(object)->_texture);
		}
		virtual void showScr() noexcept
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
				SDL_DestroyTexture(i.tex);
			SDL_DestroyRenderer(_renderer);
		}
		bool valid=false;
	private:
		SDL_Renderer* _renderer;
		std::vector<TextureEntry> _textures;
		//				^
		//              |
		//              +-----------+
		//                          |
		std::map<SDL_Surface*, uint32_t> _surfIndexes;
		//TODO: replace vector with map ^^^ teporary solution
	};
};