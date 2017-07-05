#pragma once
#include "uSurface.h"
namespace utl
{
	typedef SDL_Point uXY;
	typedef SDL_Rect Rect;
	/*TODO update to use class uResource*/
	/*class uDisplayObject
	{
	public:
		uDisplayObject(std::string texName);
		void load();
		void load(SDL_Renderer* renderer);
		void unload();
		SDL_Texture* getTexture();
		virtual ~uDisplayObject();

		uXY coords;
	private:
		uSurface _softwareTexture;	//stored in RAM
		SDL_Texture* _texture;		//stored in Graphic card
		bool _isLoaded;				//is loaded as as texture to SDL_Renderer?

	};*/
}