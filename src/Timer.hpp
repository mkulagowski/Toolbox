#pragma once

#include <chrono>
#include <type_traits>

template<typename RetT = double, typename ResT = std::milli, typename ClockT = std::chrono::steady_clock>
class Timer
{
	//static_assert(std::chrono::is_clock<ClockT>::value, "ClockT must be a clock type from std::chrono!");
	//static_assert(std::is_same<ResT, std::ratio>::value, "ResT must be an std::ratio type!");
	static_assert(std::is_arithmetic<RetT>::value, "RetT must be a numbr type!");

	using DurT = std::chrono::duration<RetT, ResT>;
private:
    std::chrono::time_point<ClockT> mStart; // start point

public:
	Timer() {};
	Timer(bool callStart) { if (callStart) Start(); };

	template<typename F, typename ...Args>
	static auto measureExecution(F&& func, Args&&... args)
	{
		static_assert(std::is_invocable<F, Args...>::value, "func parameter must be invocable!");

		auto tmr = Timer(true);
		std::invoke(std::forward<decltype(func)>(func), std::forward<Args>(args)...);
		return tmr.Stop();
	}

    void Start() {
		mStart = ClockT::now();
	}

	DurT Stop() {
		return ClockT::now() - mStart;
	}
};

