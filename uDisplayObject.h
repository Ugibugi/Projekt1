#pragma once
#include "uTarget.h"
#include "uResource.h"
#include "uDisplayManager.h"

namespace utl
{
	
	class uDisplayObject
	{
	public:
		uDisplayObject() :active(true), _resName(), _target(nullptr) {}
		uDisplayObject(std::string resName, uTarget* targetToBind = nullptr) : active(true), _resName(resName), _target(targetToBind) {}
		inline uTarget* getTarget() { return _target; }
		inline void setXY(int x, int y) { _target->x = x; _target->y = y; }
		inline void setXY(uDisplayObject* object) { _target->x = object->getTarget()->x; _target->y = object->getTarget()->y; }

		inline void setXYZ(int x, int y, int z) { _target->x = x; _target->y = y; _target->z = z; }
		

		inline void setWH(int w, int h) { _target->w = w; _target->h = h; }
		inline void setWH(uDisplayObject* object) { _target->w = object->getTarget()->w; _target->h = object->getTarget()->h; }

		inline void setWHD(int w, int h, int d) { _target->w = w; _target->h = h; _target->d = d; }


		inline void setTarget(uTarget target) { *_target = target; }
		inline void setNewTarget(uTarget* target) { _target = target; }
		
		virtual ~uDisplayObject();

		bool active;
	protected:
		std::string _resName;
	private:
		uTarget* _target;
		
		
	};
	/*//OLD
	typedef uResource<SDL_Surface, uResourceManager::loadImage, SDL_FreeSurface>::Handle uImage;
	class uDisplayObject
	{
	public:
		uDisplayObject() :active(true), _target(std::make_shared<SDL_Rect>()) {}
		uDisplayObject(std::string texName, std::shared_ptr<SDL_Rect> rectToBind = std::make_shared<SDL_Rect>()) : active(true), srcImage(texName), _target(rectToBind) {}
		inline int getTexture() { return _texture; }



		inline SDL_Rect* getTarget() { return _target.get(); }
		inline void setXY(int x, int y) { _target->x = x; _target->y = y; }
		inline void setWH(int w, int h) { _target->w = w; _target->h = h; }
		inline void setCenter(int x, int y) { _target->x = x + _target->w / 2; _target->y = y + _target->h / 2;}
		inline void setTarget(SDL_Rect rect) { *_target = rect; }
		inline void uDisplayObject::setImage(std::string&& path)
		{
			srcImage.set(std::forward<std::string>(path));
			uDisplayManager::reloadObjectTexture(this);
		}
		inline SDL_Surface* uDisplayObject::getImage()
		{
			return srcImage.get();
		}
	
		virtual ~uDisplayObject();

		int _texture;
		bool active;
		std::shared_ptr<SDL_Rect> _target;
	private:
		uImage srcImage;
		
	};*/
}