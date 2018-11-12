#pragma once
#include <memory>
#include "uTarget.h"
#include "uMath.h"
#include "SDL.h"
namespace utl
{

	class uPhysicsObject
	{
	public:
		uPhysicsObject() :active(true), _box(std::make_shared<uTarget>()) {}
		uPhysicsObject(std::shared_ptr<uTarget> rectToBind = std::make_shared<uTarget>())
			: active(true), _box(rectToBind)
		{}



		inline uTarget* getTarget() { return _box.get(); }
		inline void setXY(int x, int y) { _box->x = x; _box->y = y; }
		inline void setWH(int w, int h) { _box->w = w; _box->h = h; }
		inline void setCenter(int x, int y) { _box->x = x + _box->w / 2;  _box->y = y + _box->h / 2; }
		inline void setTarget(uTarget rect) { *_box = rect; }
		inline void setTarget(std::shared_ptr<uTarget> rectToBind) { _box = rectToBind; }

		bool active; // inactive objects don't move but are still solid
		float mass;
		uVec2D velocity;
		std::shared_ptr<uTarget> _box;
	private:
		uint8_t _id;
		uint8_t _groupId;

	};
}