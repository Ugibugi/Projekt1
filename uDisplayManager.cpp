#include "uDisplayManager.h"
#include <iostream>
using namespace utl;

SDL_Renderer* uDisplayManager::_renderer;
SDL_Window* uDisplayManager::_window;
bool uDisplayManager::_initialized;
std::vector<uDisplayObject*> uDisplayManager::_loadedObjects;

void uDisplayManager::init(SDL_Window* window,SDL_Renderer* renderer)
{
	_window = window;
	_renderer = renderer;
	_initialized = true;

}
//TODO fix setting width and height
void uDisplayManager::loadObject(uDisplayObject* object)
{
	object->_texture = SDL_CreateTextureFromSurface(_renderer, object->srcImage.get());//first get - Resource is loaded
	object->setWH(object->srcImage.get()->w, object->srcImage.get()->h); // set default dismensions of an image
	_loadedObjects.push_back(object);
}
void uDisplayManager::draw()
{
	SDL_RenderClear(_renderer);
	for (auto object : _loadedObjects)
	{
		if (SDL_RenderCopy(_renderer, object->getTexture(), NULL, object->getTarget()) == -1)
			std::cout << SDL_GetError();
	}
	SDL_RenderPresent(_renderer);
}
void uDisplayManager::close()
{

}