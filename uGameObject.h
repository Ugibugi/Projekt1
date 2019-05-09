#pragma once
#include <type_traits>
#include "uPhysicsObject.h"
#include "uDisplayObject.h"
namespace utl
{
	template<typename PhysicsT,typename DisplayT>
	class uGameObject
	{
		static_assert(std::is_base_of<uDisplayObject, DisplayT>::value);
		static_assert(std::is_base_of<uPhysicsObject, PhysicsT>::value);
		PhysicsT _myPhys;
		DisplayT _myDisp;
		
	public:
		//TODO RULE OF THREE
		uGameObject() noexcept
		{
			_myPhys.setNewTarget(&_commonTarget);
			_myDisp.setNewTarget(&_commonTarget);
		}
		uGameObject(const uGameObject<PhysicsT,DisplayT>& other)
		{
			_myPhys.mass = other.Phys.mass;
			_myPhys._groupId = other.Phys._groupId;
			
			_myDisp._resName = other.Disp._resName;
			_commonTarget = other._commonTarget;

			_myPhys.setNewTarget(&_commonTarget);
			_myDisp.setNewTarget(&_commonTarget);
			
		}
		void setTarget(uTarget t)
		{
			_commonTarget = t;
		}
		uTarget& Target() { return _commonTarget; }
		PhysicsT& Phys = _myPhys;
		DisplayT& Disp = _myDisp;
	protected:	
		uTarget _commonTarget;

	};
}

