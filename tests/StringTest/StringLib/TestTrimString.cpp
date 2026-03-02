#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


KE_TEST(trimString)
{
	ASSERT_EQUAL(ke::trim_string("  hello  "), "hello");
	ASSERT_EQUAL(ke::trim_string("  hello"), "hello");
	ASSERT_EQUAL(ke::trim_string("hello  "), "hello");
	ASSERT_EQUAL(ke::trim_string("hello"), "hello");
	ASSERT_EQUAL(ke::trim_string("  hello world  "), "hello world");
	ASSERT_EQUAL(ke::trim_string("  hello world"), "hello world");
	ASSERT_EQUAL(ke::trim_string("hello world  "), "hello world");
	ASSERT_EQUAL(ke::trim_string("hello world"), "hello world");
	ASSERT_EQUAL(ke::trim_string("\t \nhello\t\n"), "hello");
	ASSERT_EQUAL(ke::trim_string("\t \nhello\t\nworld\t\n"), "hello\t\nworld");
	ASSERT_EQUAL(ke::trim_string(""), "");

	ASSERT_EQUAL(ke::trim_string("\thello ", { ' ' }), "\thello");
	ASSERT_EQUAL(ke::trim_string(" hello\t", { ' ' }), "hello\t");
	ASSERT_EQUAL(ke::trim_string(" hello ", {}), " hello ");
}