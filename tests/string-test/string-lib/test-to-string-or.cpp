#include <keul/keul.hpp>
#include <keul/unit-tests.hpp>

KE_TEST(toStringOr)
{
	ASSERT_EQUAL(ke::to_string_or(0), "0");
	ASSERT_EQUAL(ke::to_string_or(1), "1");
	ASSERT_EQUAL(ke::to_string_or(123), "123");
	ASSERT_EQUAL(ke::to_string_or(-123), "-123");
	ASSERT_EQUAL(ke::to_string_or(1234567890), "1234567890");
	ASSERT_EQUAL(ke::to_string_or(-1234567890), "-1234567890");
	ASSERT_EQUAL(ke::to_string_or(1234567890123456789), "1234567890123456789");
	ASSERT_EQUAL(ke::to_string_or(-1234567890123456789), "-1234567890123456789");
	ASSERT_EQUAL(ke::to_string_or("1234"), "1234");

	ASSERT_EQUAL(ke::to_string_or(0.0f), "0");
	ASSERT_EQUAL(ke::to_string_or(1.0f), "1");
	ASSERT_EQUAL(ke::to_string_or(1.5f), "1.5");
	ASSERT_EQUAL(ke::to_string_or(-1.5f), "-1.5");
	ASSERT_EQUAL(ke::to_string_or(1.23456789), "1.23456789");
	ASSERT_EQUAL(ke::to_string_or(-1.23456789), "-1.23456789");
	ASSERT_EQUAL(ke::to_string_or("1.9"), "1.9");

	ASSERT_EQUAL(ke::to_string_or(ke::ClosedRange(0, 10).to_string()), "[0, 10]");
	ASSERT_EQUAL(ke::to_string_or(ke::OpenRange(0, 10)), "(0, 10)");
	ASSERT_EQUAL(ke::to_string_or(ke::HalfOpenRange(0, 10)), "[0, 10)");

	struct TestStruct
	{
		int a;
		float b;
		std::string c;
	};

	ASSERT_EQUAL(ke::to_string_or(TestStruct{}, "???"), "???");
	ASSERT_EQUAL(ke::to_string_or(TestStruct{}, ""), "");
	ASSERT_EQUAL(ke::to_string_or(TestStruct{}, "?"), "?");
	ASSERT_EQUAL(ke::to_string_or(1), "1");
	ASSERT_EQUAL(ke::to_string_or(1.5f), "1.5");
	ASSERT_EQUAL(ke::to_string_or("1234"), "1234");
}


KE_TEST(toStringOrOrError)
{
	struct TestStruct
	{
		int a;
		float b;
		std::string c;
	};

	ASSERT_ERROR(ke::to_string_or_error(TestStruct{}), ke::Error::InvalidType);
	ASSERT_EQUAL(ke::to_string_or_error(1), "1");
	ASSERT_EQUAL(ke::to_string_or_error(1.5f), "1.5");
	ASSERT_EQUAL(ke::to_string_or_error("1234"), "1234");
}
