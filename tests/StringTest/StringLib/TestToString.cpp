#include <KEUL/Utility.h>
#include <KEUL/Testing.h>

KE_TEST(toString)
{
	ASSERT_EQUAL(ke::toString(0), "0");
	ASSERT_EQUAL(ke::toString(1), "1");
	ASSERT_EQUAL(ke::toString(123), "123");
	ASSERT_EQUAL(ke::toString(-123), "-123");
	ASSERT_EQUAL(ke::toString(1234567890), "1234567890");
	ASSERT_EQUAL(ke::toString(-1234567890), "-1234567890");
	ASSERT_EQUAL(ke::toString(1234567890123456789), "1234567890123456789");
	ASSERT_EQUAL(ke::toString(-1234567890123456789), "-1234567890123456789");
	ASSERT_EQUAL(ke::toString("1234"), "1234");

	ASSERT_EQUAL(ke::toString(0.0f), "0");
	ASSERT_EQUAL(ke::toString(1.0f), "1");
	ASSERT_EQUAL(ke::toString(1.5f), "1.5");
	ASSERT_EQUAL(ke::toString(-1.5f), "-1.5");
	ASSERT_EQUAL(ke::toString(1.23456789), "1.23456789");
	ASSERT_EQUAL(ke::toString(-1.23456789), "-1.23456789");
	ASSERT_EQUAL(ke::toString("1.9"), "1.9");

	ASSERT_EQUAL(ke::toString(ke::ClosedRange(0, 10)), "[0, 10]");
	ASSERT_EQUAL(ke::toString(ke::OpenRange(0, 10)), "(0, 10)");
	ASSERT_EQUAL(ke::toString(ke::HalfOpenRange(0, 10)), "[0, 10)");
}
