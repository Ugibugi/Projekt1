#pragma once
#include <unordered_map>
#include <set>
#include <memory>
#include "uPhysicsObject.h"
#include "uCollisionHandler.h"
namespace utl
{

	class uPhysicsRuleset { public: void process(uPhysicsObject*, double time) {} };//placeholder
	class uPhysicsManager
	{
	public:
		uint32_t addObject(uPhysicsObject* object,void* owner)
		{
			object->_id = _objects.size();
			_ownerMap[object->_id] = owner;
			_objects.push_back(object);

			if (object->_groupId != 0)_groupMap[_objects.back()->_groupId].insert(object->_id);
			return object->_id;
			//_collisionHandler.registerGroup<>(object->_groupId);
		}
		uCollisionHandler& Handler() noexcept { return _collisionHandler; }
		uPhysicsRuleset& Ruleset() noexcept { return _ruleset; }

		void Update(double timeUnits)
		{
			for (auto object : _objects)
			{
				if (object->active) _ruleset.process(object,timeUnits);
			}
			CheckCollisions();
		}
		void CheckCollisions()
		{
			//Naive implementation for now
			for (size_t i = 0; i < _objects.size(); ++i)
			{
				if (_objects[i]->solid == false) continue;
				for (size_t j = i + 1; j < _objects.size(); ++j)
				{
					if (_objects[j]->solid == false) continue;
					if (rectIntersect(_objects[i]->getTarget(), _objects[j]->getTarget())) //TODO ruleset customisable
					{
						SDL_Event e;
						e.type = SDL_USEREVENT;
						e.user.data1 = _ownerMap.at(_objects[i]->_id);
						e.user.data2 = _ownerMap.at(_objects[j]->_id);
						if(SDL_PushEvent(&e)<1)std::cout<<"COLLISION ERROR";
						//_collisionHandler.call(_objects[i]->_groupId, _objects[j]->_groupId, _objects[i], _objects[j]);
					}
				}
			}
		}

	private:
		std::vector<uPhysicsObject*> _objects;
		uCollisionHandler _collisionHandler;
		std::unordered_map<uint32_t, std::set<uint32_t>> _groupMap;
		std::unordered_map<uint32_t, void*> _ownerMap;
		uPhysicsRuleset _ruleset;
		bool rectIntersect(const uTarget* r1, const uTarget* r2)
		{
			const auto rangeIntersect = [](int min1, int max1, int min2, int max2) constexpr 
			{
				return min2 < max1 && max2 > min1;
			};
			return rangeIntersect(r1->x, r1->x + r1->w, r2->x, r2->x + r2->w) && rangeIntersect(r1->y, r1->y + r1->h, r2->y, r2->y + r2->h);
		}

	};
}
