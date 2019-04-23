#pragma once
#include "uFunctionStorage.h"
#include <chrono>
namespace utl
{
	class uTimer_base
	{
	public:
		uTimer_base()
		{
			_lastTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
		}
		virtual void updateTimer() = 0;

		template<typename... Types>
		void addCall(uint32_t call_id, Types... args)
		{
			_timedCalls.addCall(call_id, args...);
		}
		void removeCall(uint32_t call_id)
		{
			_timedCalls.removeCall(call_id);
		}
	protected:
		uBindedFunctionStorage<> _timedCalls;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> _lastTime;
	};


	class uSynchronisedTimer : public uTimer_base
	{
	public:
		uSynchronisedTimer(uint32_t miliseconds)
			:_duration(miliseconds)
		{
			//_lastTime.time_since_epoch() = _lastTime.time_since_epoch() - (_lastTime.time_since_epoch() % miliseconds); 
			//left side ist const so it has no effect. ( ? ) TODO examine this
		}
		~uSynchronisedTimer() = default;
		virtual void updateTimer() override
		{
			const auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
			if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastTime) > _duration)
			{
				_lastTime = currentTime;
				_timedCalls.CallAll();
			}

		}
	private:
		std::chrono::milliseconds _duration;
	};


	class uDelayTimer : protected uTimer_base
	{
		struct DelayedCall
		{
			uint32_t milisecondsLeft;
			uint32_t callId;
		};
	public:
		template<typename... Types>
		void DelayCall(uint32_t delay, Types... args)
		{
			_callList.push_back({ delay,_idCounter });
			_timedCalls.addCall(_idCounter, args...);
			_idCounter++;
		}
		virtual void updateTimer() override
		{
			const auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
			const auto deltaTime = currentTime - _lastTime;

			for (auto call = _callList.begin(); call != _callList.end(); ++call)
			{
				call->milisecondsLeft -= deltaTime.count();
				if (call->milisecondsLeft <= 0)
				{
					_timedCalls.Call(call->callId);
					_timedCalls.removeCall(call->callId);
					_callList.erase(call);
				}
			}
		}
	private:
		uint32_t _idCounter=0;
		std::list<DelayedCall> _callList;
		
	};
}
