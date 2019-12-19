#pragma once
#include <SDL2/SDL.h>

namespace utl
{
	class uDisplayObject;
	class uRenderer
	{
	public:
		virtual int loadTexture(SDL_Surface* image) = 0;
		virtual void destroyTexture(int texId) = 0;
		virtual void drawObject(uDisplayObject* object) = 0;
		virtual void loadObject(uDisplayObject* object) = 0;
		virtual void reloadObject(uDisplayObject* object) = 0;
		virtual void destroyObject(uDisplayObject* object) = 0;
		virtual void showScr() = 0;
		virtual void clearScr() = 0;
		virtual ~uRenderer() = default;
	protected:
	private:
		
	};
}