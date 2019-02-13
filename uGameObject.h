#pragma once
#include <type_traits>
#include "uPhysicsObject.h"
#include "uDisplayObject.h"
namespace utl
{
	template<typename PhysicsT,typename DisplayT>
	class uGameObject :public PhysicsT, public DisplayT
	{
		static_assert(std::is_base_of<uDisplayObject, DisplayT>::value);
		static_assert(std::is_base_of<uPhysicsObject, PhysicsT>::value);
		
	public:
		//TODO: get rid of this nasty hack and add unified methods for manipulating target
		typedef PhysicsT PT;
		typedef DisplayT DT;
		//TODO RULE OF THREE
		uGameObject()
		{
			PT::setNewTarget(&_commonTarget);
			DT::setNewTarget(&_commonTarget);
		}
		uGameObject(const uGameObject<PT, DT>& other)
		{
			PT::mass = other.PT::mass;
			PT::_groupId = other.PT::_groupId;
			
			DT::_resName = other.DT::_resName;
			_commonTarget = other._commonTarget;

			PT::setNewTarget(&_commonTarget);
			DT::setNewTarget(&_commonTarget);
			
		}
		void setTarget(uTarget t)
		{
			_commonTarget = t;
		}
		uTarget& Target() { return _commonTarget; }
		
	protected:
		
		uTarget _commonTarget;

	};
}

