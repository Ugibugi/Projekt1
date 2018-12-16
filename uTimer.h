#pragma once
#include "uFunctionStorage.h"
#include <chrono>
namespace utl
{
	class uSynchronisedTimer
	{
	public:
		uSynchronisedTimer(uint32_t miliseconds)
			:_duration(miliseconds)
		{
			_lastTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
			_lastTime.time_since_epoch() = _lastTime.time_since_epoch() - (_lastTime.time_since_epoch() % miliseconds);

		}
		~uSynchronisedTimer() = default;
		void updateTimer()
		{
			auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
			if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastTime) > _duration)
			{
				_lastTime = currentTime;
				_timedCalls.CallAll();
			}

		}
		template<typename... Types>
		void addCall(uint32_t call_id, Types... args)
		{
			_timedCalls.addCall(call_id, args...);
		}
		void removeCall(uint32_t call_id)
		{
			_timedCalls.removeCall(call_id);
		}
	private:
		uBindedFunctionStorage<> _timedCalls;
		std::chrono::time_point<std::chrono::steady_clock,std::chrono::milliseconds> _lastTime;
		std::chrono::milliseconds _duration;
	};

}
