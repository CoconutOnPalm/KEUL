#include <KEUL/Utility.h>
#include <KEUL/Testing.h>


KE_TEST(trimString)
{
	ASSERT_EQUAL(ke::trimString("  hello  "), "hello");
	ASSERT_EQUAL(ke::trimString("  hello"), "hello");
	ASSERT_EQUAL(ke::trimString("hello  "), "hello");
	ASSERT_EQUAL(ke::trimString("hello"), "hello");
	ASSERT_EQUAL(ke::trimString("  hello world  "), "hello world");
	ASSERT_EQUAL(ke::trimString("  hello world"), "hello world");
	ASSERT_EQUAL(ke::trimString("hello world  "), "hello world");
	ASSERT_EQUAL(ke::trimString("hello world"), "hello world");
	ASSERT_EQUAL(ke::trimString("\t \nhello\t\n"), "hello");
	ASSERT_EQUAL(ke::trimString("\t \nhello\t\nworld\t\n"), "hello\t\nworld");
	ASSERT_EQUAL(ke::trimString(""), "");

	ASSERT_EQUAL(ke::trimString("\thello ", { ' ' }), "\thello");
	ASSERT_EQUAL(ke::trimString(" hello\t", { ' ' }), "hello\t");
	ASSERT_EQUAL(ke::trimString(" hello ", {}), " hello ");
}