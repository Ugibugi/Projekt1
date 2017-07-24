#pragma once
#include <map>
#include <memory>
#include <utility>
#include <functional>
namespace utl
{
	template<typename T = uint32_t>
	class uFunctionStorage
	{
	public:
		//x.addCall(call_id, function_ptr, arg1, arg2 ... );
		template<typename... Types>
		void addCall(T call_id, Types&&... args)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.erase(call_id);

			std::function<void(void)> function = std::bind(std::forward<Types>(args)...);
			_functionCalls.emplace(std::make_pair(call_id, function));
		}
		void Call(T call_id)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.at(call_id)();
		}
	private:
		std::map<T, std::function<void(void)>> _functionCalls;
	};
}
