#pragma once
#include <vector>
#include <SDL.h>

#include <unordered_set>
namespace utl
{ 
	class uDisplayObject;
	class uDisplayManager
	{
		friend class uDisplayObject;
	public:
		
		static void init(SDL_Window* window, SDL_Renderer* renderer);
	
		static void loadObject(uDisplayObject* object);
		static inline SDL_Renderer* getRenderer() { return _renderer; }
		static void draw();
		static void close();
		static void clearObjects();
	private:
		static void drawObject(uDisplayObject* object);
		static void reloadObjectTexture(uDisplayObject* object);
		static SDL_Renderer* _renderer;
		static SDL_Window* _window;
		static bool _initialized;
		static std::unordered_set<uDisplayObject*> _loadedObjects;
	};
}
