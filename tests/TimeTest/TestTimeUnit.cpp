#include <KEUL/UnitTests.hpp>
#include <KEUL/Time/Timer.hpp>

#include <format>

#ifdef _MSC_VER
#pragma execution_character_set( "utf-8" )
#endif


KE_TEST(TimeUnit)
{
	ASSERT_EQUAL(std::format("{}", ke::TimeUnit::nanoseconds), "ns");
	ASSERT_EQUAL(std::format("{}", ke::TimeUnit::microseconds), "\u00B5s");
	ASSERT_EQUAL(std::format("{}", ke::TimeUnit::miliseconds), "ms");
	ASSERT_EQUAL(std::format("{}", ke::TimeUnit::seconds), "s");
	ASSERT_EQUAL(std::format("{}", ke::TimeUnit::minutes), "min");
}
