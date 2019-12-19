#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <type_traits>
//#include "uResource.h"
#include <stdexcept>
namespace utl
{
	/*
	*
	* Here all resources are strored in form of uResource_base pointers to uResource,  
	*  one can access a resourrce by declaring a variable of type uResource<>::Handle and calling .set() on it,
	*  this method calls  uResourceManager::get which returns accordingly casted shared_ptr. 
	* 
	* This class allows accessing given resource multiple times but loading it only once.
	*
	*
	*
	*
	*/
	class uResource_base;
	class uResourceManager
	{

	public:
		//TODO This function belongs in SDL utility code
		static SDL_Surface* loadImage(std::string name)
		{
			return IMG_Load(name.c_str());
		}
		//
		//TODO add more safety
		template<typename T>
		static std::shared_ptr<T> get(std::string name)
		{
			//The return type has to be derived form uResource_base
			static_assert(std::is_base_of<uResource_base, T>::value, "ERROR: template argument in uResourceManager::get is not a child of uResource_base.");
			std::shared_ptr<T> ret;

			if (_resources.count(name) == 0)
			{
				//if resource is requested for the first time,
				// create it and load it from disk with methods passed as
				// Creator and deleter in uResource class.
				std::shared_ptr<uResource_base> ptr(new T(name));
				if (!ptr->load())
					std::cout << "Error loading resource: " << ptr->getName();


				//cast ptr to a return type and store it for later use
				ret = std::static_pointer_cast<T>(ptr);
				_resources.insert(std::make_pair(name, ptr));
			}
			else
			{
				//if resource was requested earlier just cast from an existing resource
				ret = std::static_pointer_cast<T>(_resources.at(name));
				ret->load(); //load if hasn't been loaded yet
			}

			if (!ret) throw std::runtime_error("Couldn't load resource " + name); //Should throw on any error in Creator function
			return ret;
		}

	private:
		static std::string _resDirPath;
		//TODO buffer often requested data
		static std::unordered_map<std::string,std::shared_ptr<uResource_base>> _resources;
		
	};
}