#pragma once
#include "uResource.h"

namespace utl
{
	typedef uResource<SDL_Surface, uResourceManager::loadImage, SDL_FreeSurface>::Handle uImage;

	/*TODO update to use class uResource*/
	class uDisplayObject
	{
	public:
		uDisplayObject() {}
		uDisplayObject(std::string texName) :srcImage(texName){}
		inline SDL_Texture* getTexture() { return _texture; }



		inline SDL_Rect* getTarget() { return &_target; }
		inline void setXY(int x, int y) { _target.x = x; _target.y = y; }
		inline void setWH(int w, int h) { _target.w = w; _target.h = h; }
		inline void setTarget(SDL_Rect rect) { _target = rect; }

		virtual ~uDisplayObject();

		SDL_Texture* _texture;
		uImage srcImage;
	private:
		
		SDL_Rect _target;
		
	};
}