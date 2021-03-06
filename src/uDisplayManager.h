#pragma once
#include <vector>
#include <SDL2/SDL.h>

#include <unordered_set>
#include "uRenderer.h"
namespace utl
{ 
	class uDisplayObject;
	class uDisplayManager
	{
		friend class uDisplayObject;
	public:
		
		static void init(uRenderer* renderer) noexcept;
	
		static void loadObject(uDisplayObject* object);
		static inline uRenderer* getRenderer() noexcept { return _renderer; }
		static void draw();
		static void close();
		static void clearObjects();
		static void reloadObject(uDisplayObject* object);
	private:
		static uRenderer* _renderer;
		static bool _initialized;
		static std::unordered_set<uDisplayObject*> _loadedObjects;
	};
}
