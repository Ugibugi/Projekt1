#include "uSurface.h"
#include "ResourceManager.h"
#include "uDisplayManager.h"
#include <SDL.h>
#include <cassert>
using namespace utl;


void uSurface::load()
{
	if (!_isLoaded)
	{
		_surface = uResourceManager::getImage(_resName);
		

		/*if (flags == TEXTURE)
		{
			assert(manager != nullptr);
			_texture = SDL_CreateTextureFromSurface(manager->getRenderer(),_surface);
			SDL_FreeSurface(_surface);
			_isTexture = true;
			SDL_CreateSurfaceF
		}*/
		_isLoaded = true;
	}


}
void uSurface::unload()
{
	if (_isLoaded)
	{
		SDL_FreeSurface(_surface);
	}
	_isLoaded = false;
}
SDL_Surface* uSurface::getSurface()
{
	if (!_isLoaded)
		load();
	return _surface;
}
uSurface::~uSurface()
{
	unload();
}


