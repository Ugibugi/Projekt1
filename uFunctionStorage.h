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
		//x.addCall(call_id, function_ptr, arg1, arg2 ... );
		template<typename... Types>
		void addCall(uint32_t call_id, Types&&... args)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.erase(call_id);

			std::function<void(void)> function = std::bind(std::forward<Types>(args)...);
			_functionCalls.emplace(std::make_pair(call_id, function));
		}
		void Call(uint32_t call_id)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.at(call_id)();
		}
	private:
		std::map<uint32_t, std::function<void(void)>> _functionCalls;
	};
}
