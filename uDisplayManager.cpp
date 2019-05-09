#include "uDisplayManager.h"
#include "uDisplayObject.h"

#include <iostream>
using namespace utl;

uRenderer* uDisplayManager::_renderer;
bool uDisplayManager::_initialized;
std::unordered_set<uDisplayObject*> uDisplayManager::_loadedObjects;

void uDisplayManager::init(uRenderer* renderer) noexcept
{

	_renderer = renderer;
	_initialized = true;

}
void uDisplayManager::loadObject(uDisplayObject* object)
{
	_renderer->loadObject(object);
	//object->_texture = _renderer->loadTexture(object->getImage());
	//object->setWH(object->getImage()->w, object->getImage()->h); // set default dismensions of an image
	_loadedObjects.insert(object);
}
void uDisplayManager::draw()
{
	_renderer->clearScr();
	for (auto object : _loadedObjects)
	{
		if (object->active)
		{
			_renderer->drawObject(object);
		}
	}
	_renderer->showScr();
}

void uDisplayManager::reloadObject(uDisplayObject* object)
{
	
	if (_loadedObjects.count(object)==1)
	{
		_renderer->reloadObject(object);
	}
}
void uDisplayManager::clearObjects()
{
	for (auto object : _loadedObjects)
	{
		_renderer->destroyObject(object);
	}
	_loadedObjects.clear();
}
void uDisplayManager::close()
{

}

