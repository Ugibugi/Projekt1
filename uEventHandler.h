#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include "uFunctionStorage.h"
namespace utl
{
	template<typename ID, typename EventInfo, typename EventSource>
	class uEventHandler
	{
		typedef std::function<void(Info*)> EventHandler;

	public:
		void addEvent(ID Event_id, EventHandler handlerFunc);
		void processEvents()
		{

		}
		void removeEvent(ID Event_id);
	private:
		std::vector<ID> _eventIds;
		uFunctionStorage<ID, EventInfo*> _handlerFuns;

	};
}

