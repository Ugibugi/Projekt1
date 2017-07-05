#pragma once
#include <SDL.h>
#include <string>
namespace utl
{

	class uSurface
	{
	public:
		uSurface(std::string name, bool isAnimation = false)
			:_resName(name), _isAnimation(isAnimation), _isLoaded(false) {}

		void load();	//load into the RAM as SDL_surface
		void unload();	//free memory


		SDL_Surface* getSurface();	
		inline bool isLoaded() const { return _isLoaded; }
		~uSurface();

	private:

		std::string _resName;	//name of the resource for the resource manager
		bool _isAnimation;
		bool _isLoaded;			//does the resource needs to be loaded from Hard Disk

		SDL_Surface* _surface;
		
	};
}
