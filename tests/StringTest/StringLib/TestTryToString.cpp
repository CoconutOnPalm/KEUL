#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>

KE_TEST(toStringOr)
{
	ASSERT_EQUAL(ke::toStringOr(0), "0");
	ASSERT_EQUAL(ke::toStringOr(1), "1");
	ASSERT_EQUAL(ke::toStringOr(123), "123");
	ASSERT_EQUAL(ke::toStringOr(-123), "-123");
	ASSERT_EQUAL(ke::toStringOr(1234567890), "1234567890");
	ASSERT_EQUAL(ke::toStringOr(-1234567890), "-1234567890");
	ASSERT_EQUAL(ke::toStringOr(1234567890123456789), "1234567890123456789");
	ASSERT_EQUAL(ke::toStringOr(-1234567890123456789), "-1234567890123456789");
	ASSERT_EQUAL(ke::toStringOr("1234"), "1234");

	ASSERT_EQUAL(ke::toStringOr(0.0f), "0");
	ASSERT_EQUAL(ke::toStringOr(1.0f), "1");
	ASSERT_EQUAL(ke::toStringOr(1.5f), "1.5");
	ASSERT_EQUAL(ke::toStringOr(-1.5f), "-1.5");
	ASSERT_EQUAL(ke::toStringOr(1.23456789), "1.23456789");
	ASSERT_EQUAL(ke::toStringOr(-1.23456789), "-1.23456789");
	ASSERT_EQUAL(ke::toStringOr("1.9"), "1.9");

	ASSERT_EQUAL(ke::toStringOr(ke::ClosedRange(0, 10).toString()), "[0, 10]");
	ASSERT_EQUAL(ke::toStringOr(ke::OpenRange(0, 10)), "(0, 10)");
	ASSERT_EQUAL(ke::toStringOr(ke::HalfOpenRange(0, 10)), "[0, 10)");

	struct TestStruct
	{
		int a;
		float b;
		std::string c;
	};

	ASSERT_EQUAL(ke::toStringOr(TestStruct{}, "???"), "???");
	ASSERT_EQUAL(ke::toStringOr(TestStruct{}, ""), "");
	ASSERT_EQUAL(ke::toStringOr(TestStruct{}, "?"), "?");
	ASSERT_EQUAL(ke::toStringOr(1), "1");
	ASSERT_EQUAL(ke::toStringOr(1.5f), "1.5");
	ASSERT_EQUAL(ke::toStringOr("1234"), "1234");
}


KE_TEST(toStringOrOrError)
{
	struct TestStruct
	{
		int a;
		float b;
		std::string c;
	};

	ASSERT_ERROR(ke::toStringOrError(TestStruct{}), ke::Error::InvalidType);
	ASSERT_EQUAL(ke::toStringOrError(1), "1");
	ASSERT_EQUAL(ke::toStringOrError(1.5f), "1.5");
	ASSERT_EQUAL(ke::toStringOrError("1234"), "1234");
}
