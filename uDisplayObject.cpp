#include "uDisplayObject.h"



using namespace utl;


/*uDisplayObject::uDisplayObject(std::string texName)
	:_softwareTexture(texName) 
{

}

void uDisplayObject::load()
{
	_softwareTexture.load();
}

void uDisplayObject::load(SDL_Renderer * renderer)
{
	_softwareTexture.load();
	if (_isLoaded) SDL_DestroyTexture(_texture);
	_texture = SDL_CreateTextureFromSurface(renderer, _softwareTexture.getSurface());
	_isLoaded = true;
}

void uDisplayObject::unload()
{
	if (_isLoaded)SDL_DestroyTexture(_texture);
	

}

SDL_Texture* uDisplayObject::getTexture()
{
	if(_isLoaded)
		return _texture;

}

uDisplayObject::~uDisplayObject()
{
	unload();
	_softwareTexture.unload();
}*/
