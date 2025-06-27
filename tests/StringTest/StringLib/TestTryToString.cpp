#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>

KE_TEST(tryToString)
{
	ASSERT_EQUAL(ke::tryToString(0), "0");
	ASSERT_EQUAL(ke::tryToString(1), "1");
	ASSERT_EQUAL(ke::tryToString(123), "123");
	ASSERT_EQUAL(ke::tryToString(-123), "-123");
	ASSERT_EQUAL(ke::tryToString(1234567890), "1234567890");
	ASSERT_EQUAL(ke::tryToString(-1234567890), "-1234567890");
	ASSERT_EQUAL(ke::tryToString(1234567890123456789), "1234567890123456789");
	ASSERT_EQUAL(ke::tryToString(-1234567890123456789), "-1234567890123456789");
	ASSERT_EQUAL(ke::tryToString("1234"), "1234");

	ASSERT_EQUAL(ke::tryToString(0.0f), "0");
	ASSERT_EQUAL(ke::tryToString(1.0f), "1");
	ASSERT_EQUAL(ke::tryToString(1.5f), "1.5");
	ASSERT_EQUAL(ke::tryToString(-1.5f), "-1.5");
	ASSERT_EQUAL(ke::tryToString(1.23456789), "1.23456789");
	ASSERT_EQUAL(ke::tryToString(-1.23456789), "-1.23456789");
	ASSERT_EQUAL(ke::tryToString("1.9"), "1.9");

	ASSERT_EQUAL(ke::tryToString(ke::ClosedRange(0, 10).toString()), "[0, 10]");
	ASSERT_EQUAL(ke::tryToString(ke::OpenRange(0, 10)), "(0, 10)");
	ASSERT_EQUAL(ke::tryToString(ke::HalfOpenRange(0, 10)), "[0, 10)");

	struct TestStruct
	{
		int a;
		float b;
		std::string c;
	};

	ASSERT_EQUAL(ke::tryToString(TestStruct{}, "???"), "???");
	ASSERT_EQUAL(ke::tryToString(TestStruct{}, ""), "");
	ASSERT_EQUAL(ke::tryToString(TestStruct{}, "?"), "?");
	ASSERT_EQUAL(ke::tryToString(1), "1");
	ASSERT_EQUAL(ke::tryToString(1.5f), "1.5");
	ASSERT_EQUAL(ke::tryToString("1234"), "1234");
}


KE_TEST(tryToStringOrError)
{
	struct TestStruct
	{
		int a;
		float b;
		std::string c;
	};

	ASSERT_ERROR(ke::tryToStringOrError(TestStruct{}), ke::Error::InvalidArgument);
	ASSERT_EQUAL(ke::tryToStringOrError(1), "1");
	ASSERT_EQUAL(ke::tryToStringOrError(1.5f), "1.5");
	ASSERT_EQUAL(ke::tryToStringOrError("1234"), "1234");
}
