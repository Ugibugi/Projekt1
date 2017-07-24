#pragma once
#include "uFunctionStorage.h"
#include <unordered_map>
namespace utl
{

	class uInputHandler
	{
	public:
		uInputHandler();
		template<typename... Types>
		void on(uint32_t type_id, uint32_t event_id, Types... args)
		{
			_eventHandlers[type_id].addCall(event_id, args...);
		}
		~uInputHandler();
		void newEvent(uint32_t type_id, uint32_t event_id)
		{
			if (_eventHandlers.count(type_id) == 1)
				_eventHandlers.at(type_id).Call(event_id);
		}
	protected:
	private:
		//void processEvent(uint32_t type_id, uint32_t event_id);

		std::unordered_map<uint32_t, uFunctionStorage<>> _eventHandlers;

	};

}
