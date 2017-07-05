#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <memory>
#include <type_traits>
#include "uResource.h"

namespace utl
{
	class uResource_base;
	class uResourceManager
	{

	public:
		static SDL_Surface* loadImage(std::string name)
		{
			return IMG_Load(name.c_str());
		}

		//TODO add more safety
		template<typename T>
		static std::shared_ptr<T> get(std::string name)
		{
			static_assert(std::is_base_of<uResource_base, T>::value, "ERR");
			std::shared_ptr<T> ret;
			if (_resources.count(name) == 0)
			{
				std::shared_ptr<uResource_base> ptr(new T(name));
				ptr->load();
				ret = std::static_pointer_cast<T>(ptr);
				_resources.insert(std::make_pair(name, ptr));
			}
			else
			{
				ret = std::static_pointer_cast<T>(_resources.at(name));
				ret->load();
			}
			return ret;
		}

	private:
		static std::string _resDirPath;
		//TODO buffer often requested data
		static std::map<std::string,std::shared_ptr<uResource_base>> _resources;
		
	};
}