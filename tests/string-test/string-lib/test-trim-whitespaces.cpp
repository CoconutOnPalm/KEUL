#include <keul/keul.hpp>
#include <keul/unit-tests.hpp>


KE_TEST(trimWhitespaces)
{
	ASSERT_EQUAL(ke::trim_whitespaces("  hello  "), "hello");
	ASSERT_EQUAL(ke::trim_whitespaces("  hello"), "hello");
	ASSERT_EQUAL(ke::trim_whitespaces("hello  "), "hello");
	ASSERT_EQUAL(ke::trim_whitespaces("hello"), "hello");
	ASSERT_EQUAL(ke::trim_whitespaces("  hello world  "), "hello world");
	ASSERT_EQUAL(ke::trim_whitespaces("  hello world"), "hello world");
	ASSERT_EQUAL(ke::trim_whitespaces("hello world  "), "hello world");
	ASSERT_EQUAL(ke::trim_whitespaces("hello world"), "hello world");
	ASSERT_EQUAL(ke::trim_whitespaces("\t \nhello\t\n"), "hello");
	ASSERT_EQUAL(ke::trim_whitespaces("\t \nhello\t\nworld\t\n"), "hello\t\nworld");
	ASSERT_EQUAL(ke::trim_whitespaces(""), "");
	ASSERT_EQUAL(ke::trim_whitespaces("    "), "");

	ASSERT_EQUAL(ke::trim_whitespaces("\thello ", { ' ' }), "\thello");
	ASSERT_EQUAL(ke::trim_whitespaces(" hello\t", { ' ' }), "hello\t");
	ASSERT_EQUAL(ke::trim_whitespaces(" hello ", {}), " hello ");

	const std::vector<std::string> cases = { " hello ", "  hello", "hello  ", "\t\nhello\n\t " };
	const std::string check = "hello";

	for (std::string test : cases)
	{
		ke::trim_whitespaces_ref(test);
		ASSERT_EQUAL(test, check);
	}
	
}