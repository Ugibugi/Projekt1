#pragma once
#include <memory>
#include "uTarget.h"
#include "uMath.h"
namespace utl
{

	class uPhysicsObject
	{
	public:

		inline uTarget *getTarget() { return _box; }

		inline void setTarget(uTarget rect) { *_box = rect; }
		inline void setNewTarget(uTarget* rectToBind) { _box = rectToBind; }

		bool active = true; // inactive objects don't move but are still solid
		bool solid = true;
		float mass=1;
		uVec2D velocity = { 0,0 };
		uVec2D acceleration = { 0,0 };
		uTarget* _box = nullptr; 

		uint32_t _id=0;
		uint32_t _groupId=0;
	private:
		

	};
}