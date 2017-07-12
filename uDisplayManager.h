#pragma once
#include <vector>
#include <SDL.h>
#include "uDisplayObject.h"
namespace utl
{ 
	/*TODO update to use class uResource*/
	class uDisplayManager
	{
	public:
		static void init(SDL_Window* window, SDL_Renderer* renderer);
	
		static void loadObject(uDisplayObject* object);
		static inline SDL_Renderer* getRenderer() { return _renderer; }
		static void draw();
		static void close();
	private:
		static void drawObject(uDisplayObject* object);
		static SDL_Renderer* _renderer;
		static SDL_Window* _window;
		static bool _initialized;
		static std::vector<uDisplayObject*> _loadedObjects;
	};
}
