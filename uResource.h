#pragma once
#include <memory>
#include <string>
#include "uSurface.h"
#include "uResourceManager.h"

namespace utl
{

	class uResource_base
	{
	public:
		uResource_base(std::string name) :_resName(name){}
		void load() {
			if (!_isLoaded) { _load(); }_isLoaded = true;
		}
		void unload() {
			if (_isLoaded) { _unload(); }_isLoaded = false;
		}

		inline bool isLoaded() const { return _isLoaded; };
		inline std::string getName() const { return _resName; }
		virtual ~uResource_base()=default;
	protected:
		bool _isLoaded;
		std::string _resName;
	private:
		virtual void _load() = 0;
		virtual void _unload() = 0;
	};

	template<typename T, T*(*Creator)(std::string), void(*Deleter)(T*)>
	class uResource: public uResource_base
	{
		T*(*creator)(std::string) = Creator;
		void(*deleter)(T*) = Deleter;
		typedef uResource<T, Creator, Deleter> this_t;

		virtual void _load() { _resource = creator(_resName); }
		virtual void _unload() { deleter(_resource); }
		T* _resource;
	public:
		uResource(std::string name) :uResource_base(name){}
		virtual ~uResource() { unload(); };

		class Handle
		{
		public:
			Handle(){}
			Handle(std::string name) { set(name); }
			inline void load() { __ptr->load(); }
			inline void set(std::string name) { __ptr = uResourceManager::get<this_t>(name); }
			inline  T* get()
			{
				if (!(__ptr->isLoaded()))
					__ptr->load();
				return __ptr->_resource;
			}
		private:
			std::shared_ptr<this_t> __ptr;
		};
	};

	//uResource<SDL_Surface>::Handle image; //target way of using 
	//image.set("xd.bmp");

	/*OLDtemplate<>
	class uResource<SDL_Surface> : public uResource_base
	{
	private:
		virtual void _load() { _resource =  uResourceManager::loadImage(_resName); }
		virtual void _unload() { SDL_FreeSurface(_resource); }
		SDL_Surface* _resource;
	};OLD*/

	/*
		typedef uResource<SDL_Surface,uResourceManager::loadImage,SDL_FreeSurface> Image_t
		Image_t::Handle image;
		image.set("xd.bmp");
	*/
}
