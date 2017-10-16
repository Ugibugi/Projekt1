#pragma once
#include <vector>
#include <SDL.h>

#include <unordered_set>
#include "uRenderer.h"
namespace utl
{ 
	class uDisplayObject;
	class uDisplayManager
	{
		friend class uDisplayObject;
	public:
		
		static void init(uRenderer* renderer);
	
		static void loadObject(uDisplayObject* object);
		static inline uRenderer* getRenderer() { return _renderer; }
		static void draw();
		static void close();
		static void clearObjects();
	private:
		static void drawObject(uDisplayObject* object);
		static void reloadObjectTexture(uDisplayObject* object);
		static uRenderer* _renderer;
		static bool _initialized;
		static std::unordered_set<uDisplayObject*> _loadedObjects;
	};
}
