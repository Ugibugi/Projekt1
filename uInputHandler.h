#pragma once
#include "uFunctionStorage.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <SDL_events.h>
namespace utl
{
	
	//TODO Keybord matrix for multi-key input
	class uInputHandler
	{
	public:
		uInputHandler();
		//add a function to handle an event defined by type of event and event id
		//for easy SDL usage
		template<typename... Types>
		void on(uint32_t type_id, uint32_t event_id, Types... args)
		{
			_eventHandlers[type_id].addCall(event_id, args...);

			//if is keyboard event, save the binded key
			if (type_id & (SDL_KEYDOWN | SDL_KEYUP)) _bindedKeys.push_back(SDL_GetScancodeFromKey(event_id)); 
		}
		

		//Read a keyboard state and call corresponding functions
		void processKeyboard()
		{
			//get keyboard state
			int arraySize = 0;
			const uint8_t* keyArray = SDL_GetKeyboardState(&arraySize);

			for (auto vKey : _bindedKeys)
			{
				if (keyArray[vKey] == 1)
					newEvent(SDL_KEYDOWN, vKey);
				else
					newEvent(SDL_KEYUP, vKey);
			}
				

			//save keyboard state for future reference// only good for "momentary" triggers
			/*_prevKeyboardState.reset(new uint8_t[arraySize]);
			std::memcpy(_prevKeyboardState.get(), keyArray, arraySize);*/ 	
		}
		void newEvent(uint32_t type_id, uint32_t event_id)
		{
			if (_eventHandlers.count(type_id) == 1)
				_eventHandlers.at(type_id).Call(event_id);
		}

		~uInputHandler();
	protected:
	private:
		std::unique_ptr<uint8_t> _prevKeyboardState;
		std::vector<uint32_t> _bindedKeys;
		std::unordered_map<uint32_t, uFunctionStorage<>> _eventHandlers;

	};

}