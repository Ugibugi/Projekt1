#pragma once
#include <map>
#include <memory>
#include <utility>
#include "uAction.h"
namespace utl
{

	class uFunctionStorage
	{
	public:
		uFunctionStorage();
		~uFunctionStorage();

		template<typename... Types>
		void addCall(uint32_t call_id, std::function<void (Types...)> function, Types&&... args)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.erase(call_id);

			std::shared_ptr<uAction_base> ptr = std::make_shared<uAction<Types...>>(std::forward<std::function<void(Types...)>>(function), std::forward<Types>(args)...);
			_functionCalls.emplace(std::make_pair(call_id, ptr));
		}

		void Call(uint32_t call_id);


	private:;
			std::map<uint32_t, std::shared_ptr<uAction_base>> _functionCalls;
	};	
}
