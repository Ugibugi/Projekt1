#pragma once
#include "SDL.h"

namespace utl
{
	class uRenderer
	{
		friend class uDisplayObject;
	public:
		virtual int loadTexture(SDL_Surface* image) = 0;
		virtual void destroyTexture(int texId) = 0;
		virtual void drawObject(uDisplayObject* object) = 0;
		virtual void showScr() = 0;
		virtual void clearScr() = 0;
	protected:
	private:
		
	};
}