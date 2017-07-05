#pragma once
#include <tuple>
#include <functional>
namespace utl
{
	namespace helper    //iterates trough arguments
	{
		template <std::size_t... Ts>
		struct index {};

		template <std::size_t N, std::size_t... Ts>
		struct gen_seq : gen_seq<N - 1, N - 1, Ts...> {};

		template <std::size_t... Ts>
		struct gen_seq<0, Ts...> : index<Ts...> {};
	}

	class uAction_base
	{
	public:
		virtual void execute() = 0;
		virtual ~uAction_base()=default;
	};
	template <typename... Types>
	class uAction : public uAction_base
	{
	private:
		std::function<void(Types...)> function;    //proper function
		std::tuple<Types...> args;                  //arguments

		

		template <typename... Args, std::size_t... Is>
		void __function_call(std::tuple<Args...>& tup, helper::index<Is...>)
		{
			function(std::get<Is>(tup)...);         //final call function with arguments stored
		}

		template <typename... Args>
		void __function_call(std::tuple<Args...>& tup)
		{
			__function_call(tup, helper::gen_seq<sizeof...(Args)>{});   //call overloaded __function_call with sequencer
		}
	public:
		uAction(std::function<void(Types...)> func, Types&&... args) : function(func), args(std::make_tuple(std::forward<Types>(args)...))
		{}
		virtual void execute()
		{
			__function_call(args);  //call function_call with Arguments tuple
		}
	};
}