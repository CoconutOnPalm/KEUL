#include <keul/keul.hpp>
#include <keul/unit-tests.hpp>

KE_TEST(toString)
{
	ASSERT_EQUAL(ke::to_string(0), "0");
	ASSERT_EQUAL(ke::to_string(1), "1");
	ASSERT_EQUAL(ke::to_string(123), "123");
	ASSERT_EQUAL(ke::to_string(-123), "-123");
	ASSERT_EQUAL(ke::to_string(1234567890), "1234567890");
	ASSERT_EQUAL(ke::to_string(-1234567890), "-1234567890");
	ASSERT_EQUAL(ke::to_string(1234567890123456789), "1234567890123456789");
	ASSERT_EQUAL(ke::to_string(-1234567890123456789), "-1234567890123456789");
	ASSERT_EQUAL(ke::to_string("1234"), "1234");

	ASSERT_EQUAL(ke::to_string(0.0f), "0");
	ASSERT_EQUAL(ke::to_string(1.0f), "1");
	ASSERT_EQUAL(ke::to_string(1.5f), "1.5");
	ASSERT_EQUAL(ke::to_string(-1.5f), "-1.5");
	ASSERT_EQUAL(ke::to_string(1.23456789), "1.23456789");
	ASSERT_EQUAL(ke::to_string(-1.23456789), "-1.23456789");
	ASSERT_EQUAL(ke::to_string("1.9"), "1.9");

	ASSERT_EQUAL(ke::to_string(ke::ClosedRange(0, 10)), "[0, 10]");
	ASSERT_EQUAL(ke::to_string(ke::OpenRange(0, 10)), "(0, 10)");
	ASSERT_EQUAL(ke::to_string(ke::HalfOpenRange(0, 10)), "[0, 10)");
}
