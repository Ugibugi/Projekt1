#include "uDisplayManager.h"
#include "uDisplayObject.h"
#include <iostream>
using namespace utl;

SDL_Renderer* uDisplayManager::_renderer;
SDL_Window* uDisplayManager::_window;
bool uDisplayManager::_initialized;
std::unordered_set<uDisplayObject*> uDisplayManager::_loadedObjects;

void uDisplayManager::init(SDL_Window* window,SDL_Renderer* renderer)
{
	_window = window;
	_renderer = renderer;
	_initialized = true;

}
//TODO fix setting width and height
void uDisplayManager::loadObject(uDisplayObject* object)
{
	object->_texture = SDL_CreateTextureFromSurface(_renderer, object->getImage());//first get - Resource is loaded
	object->setWH(object->getImage()->w, object->getImage()->h); // set default dismensions of an image
	_loadedObjects.insert(object);
}
void uDisplayManager::draw()
{
	SDL_RenderClear(_renderer);
	for (auto object : _loadedObjects)
	{
		if (object->active)
		{
			if (SDL_RenderCopy(_renderer, object->getTexture(), NULL, object->getTarget()) == -1)
				std::cout << SDL_GetError();
		}
	}
	SDL_RenderPresent(_renderer);
}

void uDisplayManager::reloadObjectTexture(uDisplayObject* object)
{
	
	if (_loadedObjects.count(object)==1)
	{
		SDL_DestroyTexture(object->_texture);
		object->_texture = SDL_CreateTextureFromSurface(_renderer, object->getImage());
	}
}
void uDisplayManager::clearObjects()
{
	for (auto object : _loadedObjects)
	{
		SDL_DestroyTexture(object->_texture);
	}
	_loadedObjects.clear();
}
void uDisplayManager::close()
{
	for (auto object : _loadedObjects)
	{
		SDL_DestroyTexture(object->_texture);
	}
}
