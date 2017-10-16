#include "uDisplayManager.h"
#include "uDisplayObject.h"

#include <iostream>
using namespace utl;

uRenderer* uDisplayManager::_renderer;
bool uDisplayManager::_initialized;
std::unordered_set<uDisplayObject*> uDisplayManager::_loadedObjects;

void uDisplayManager::init(uRenderer* renderer)
{

	_renderer = renderer;
	_initialized = true;

}
//TODO fix setting width and height
void uDisplayManager::loadObject(uDisplayObject* object)
{
	object->_texture = _renderer->loadTexture(object->getImage());//first get - Resource is loaded
	object->setWH(object->getImage()->w, object->getImage()->h); // set default dismensions of an image
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

void uDisplayManager::reloadObjectTexture(uDisplayObject* object)
{
	
	if (_loadedObjects.count(object)==1)
	{
		_renderer->destroyTexture(object->_texture);
		object->_texture = _renderer->loadTexture(object->getImage());
	}
}
void uDisplayManager::clearObjects()
{
	for (auto object : _loadedObjects)
	{
		_renderer->destroyTexture(object->_texture);
	}
	_loadedObjects.clear();
}
void uDisplayManager::close()
{

}
