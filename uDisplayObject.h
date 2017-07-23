#pragma once
#include "uResource.h"
#include "uDisplayManager.h"
namespace utl
{
	typedef uResource<SDL_Surface, uResourceManager::loadImage, SDL_FreeSurface>::Handle uImage;

	class uDisplayObject
	{
	public:
		uDisplayObject() {}
		uDisplayObject(std::string texName) : active(true), srcImage(texName){}
		inline SDL_Texture* getTexture() { return _texture; }



		inline SDL_Rect* getTarget() { return &_target; }
		inline void setXY(int x, int y) { _target.x = x; _target.y = y; }
		inline void setWH(int w, int h) { _target.w = w; _target.h = h; }
		inline void setTarget(SDL_Rect rect) { _target = rect; }
		inline void uDisplayObject::setImage(std::string&& path)
		{
			srcImage.set(std::forward<std::string>(path));
			uDisplayManager::reloadObjectTexture(this);
		}
		inline SDL_Surface* uDisplayObject::getImage()
		{
			return srcImage.get();
		}
	
		virtual ~uDisplayObject();

		SDL_Texture* _texture;
		bool active;

	private:
		uImage srcImage;
		SDL_Rect _target;
		
	};
}