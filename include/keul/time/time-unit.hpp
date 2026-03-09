#pragma once

#include <print>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip> 

#ifdef _MSC_VER
#pragma execution_character_set( "utf-8" )
#endif



namespace ke
{
	enum class TimeUnit
	{
		nanoseconds,
		microseconds,
		milliseconds,
		seconds,
		minutes
	};


	namespace _internal
	{
		static inline std::string _time_unit_to_string(const TimeUnit timeunit)
		{
			const static std::map<ke::TimeUnit, std::string> s_time_unit_to_string = {
				{ke::TimeUnit::nanoseconds, "ns"},
				{ke::TimeUnit::microseconds, "\u00B5s"}, // µs
				{ke::TimeUnit::milliseconds, "ms"},
				{ke::TimeUnit::seconds, "s"},
				{ke::TimeUnit::minutes, "min"},
			};

			return s_time_unit_to_string.at(timeunit);
		}
	}
}


template <>
struct std::formatter<ke::TimeUnit> : std::formatter<std::string>
{
	template <typename FormatContext>
	auto format(const ke::TimeUnit time_unit, FormatContext& ctx) const
	{
		return std::formatter<std::string>::format(std::format("{}", ke::_internal::_time_unit_to_string(time_unit)), ctx);
	}
};