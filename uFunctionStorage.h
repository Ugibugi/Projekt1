#pragma once
#include <map>
#include <unordered_map>
#include <memory>
#include <utility>
#include <functional>
namespace utl
{
	template<typename T = uint32_t, typename... Args>
	class uFunctionStorage
	{
	public:
		void addCall(T call_id, std::function<void(Args...)> fun)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.erase(call_id);

			_functionCalls.emplace(std::make_pair(call_id, fun));
		}

		void removeCall(T call_id)
		{
			_functionCalls.erase(call_id);
		}
		//calls one function
		void Call(T call_id,Args... args)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.at(call_id)(args...);
		}
		//calls all functions;
		void CallAll(Args... args )
		{
			for (auto&& f : _functionCalls)
				f.second(args...);
		}

	private:
		std::unordered_map<T, std::function<void(Args...)>> _functionCalls;
	};
	template<typename T = uint32_t>
	class uBindedFunctionStorage
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

		void removeCall(T call_id)
		{
			_functionCalls.erase(call_id);
		}
		//calls one function
		void Call(T call_id)
		{
			if (_functionCalls.count(call_id) == 1)
				_functionCalls.at(call_id)();
		}
		//calls all functions;
		void CallAll()
		{
			for (auto&& f : _functionCalls)
				f.second();
		}

	private:
		std::map<T, std::function<void(void)>> _functionCalls;
	};
}
