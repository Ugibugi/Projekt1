#pragma once
#include <memory>
#include "uTarget.h"
#include "SDL.h"
namespace utl
{

	
	class uPhysicsObject
	{
	public:
		uPhysicsObject() :active(true), _box(std::make_shared<SDL_Rect>()) {}
		uPhysicsObject(std::shared_ptr<SDL_Rect> rectToBind = std::make_shared<SDL_Rect>())
			: active(true), _box(rectToBind)
		{}
		inline int getTexture() { return _texture; }



		inline SDL_Rect* getTarget() { return _box.get(); }
		inline void setXY(int x, int y) { _box->x = x; _box->y = y; }
		inline void setWH(int w, int h) { _box->w = w; _box->h = h; }
		inline void setCenter(int x, int y) { _box->x = x + _box->w / 2;  _box->y = y + _box->h / 2; }
		inline void setTarget(SDL_Rect rect) { *_box = rect; }
		inline void setTarget(std::shared_ptr<SDL_Rect> rectToBind) { _box = rectToBind; }

		int _texture;
		bool active; // inactive objects don't move but are still solid
		float mass;
		SDL_Point velocity;
		std::shared_ptr<SDL_Rect> _box;
	private:
		uint8_t _id;
		uint8_t _groupId;

	};
}