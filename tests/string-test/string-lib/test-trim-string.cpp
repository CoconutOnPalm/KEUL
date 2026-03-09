#include <keul/keul.hpp>
#include <keul/unit-tests.hpp>


KE_TEST(trimString)
{
	ASSERT_EQUAL(ke::trim_string("Hello World", 5), "He...");
	ASSERT_EQUAL(ke::trim_string("Hello World", 11), "Hello World");
	ASSERT_EQUAL(ke::trim_string("Hello World", 12), "Hello World");
	ASSERT_EQUAL(ke::trim_string("Hello World", 9), "Hello ...");
	ASSERT_EQUAL(ke::trim_string("Hello World", 8), "Hello...");
	ASSERT_EQUAL(ke::trim_string("Hello World", 0), "");
	ASSERT_EQUAL(ke::trim_string("Hello World", 1), ".");
	ASSERT_EQUAL(ke::trim_string("Hello World", 2), "..");
	ASSERT_EQUAL(ke::trim_string("Hello World", 3), "...");
	ASSERT_EQUAL(ke::trim_string("Hello World", 4), "H...");

	ASSERT_EQUAL(ke::trim_string("aaa", 3), "aaa");
	ASSERT_EQUAL(ke::trim_string("aaa", 2), "..");
	ASSERT_EQUAL(ke::trim_string("aaa", 1), ".");
	ASSERT_EQUAL(ke::trim_string("aaa", 0), "");

	ASSERT_EQUAL(ke::trim_string("a", 1), "a");
	ASSERT_EQUAL(ke::trim_string("a", 0), "");
	ASSERT_EQUAL(ke::trim_string("a", 2), "a");
	ASSERT_EQUAL(ke::trim_string("a", 3), "a");

	ASSERT_EQUAL(ke::trim_string("", 0), "");
	ASSERT_EQUAL(ke::trim_string("", 1), "");
	ASSERT_EQUAL(ke::trim_string("", 2), "");

	ASSERT_EQUAL(ke::trim_string("aaaa", 0), "");
	ASSERT_EQUAL(ke::trim_string("aaaa", 1), ".");
	ASSERT_EQUAL(ke::trim_string("aaaa", 2), "..");
	ASSERT_EQUAL(ke::trim_string("aaaa", 3), "...");
	ASSERT_EQUAL(ke::trim_string("aaaa", 4), "aaaa");
	ASSERT_EQUAL(ke::trim_string("aaaa", 5), "aaaa");
	ASSERT_EQUAL(ke::trim_string("aaaa", 6), "aaaa");
}


/*
KE_TEST(cleanTypeName)
{
	ASSERT_EQUAL(ke::cleanTypeName("std::string"), "std::string");
	ASSERT_EQUAL(ke::cleanTypeName("std::vector<int>"), "std::vector<int>");
	ASSERT_EQUAL(ke::cleanTypeName("class std::vector<std::string>"), "std::vector<std::string>");
	ASSERT_EQUAL(ke::cleanTypeName("class std::vector<std::string, std::allocator<std::string>>"), "std::vector<std::string, std::allocator<std::string>>");
	ASSERT_EQUAL(ke::cleanTypeName("class struct SomeStruct"), "SomeStruct");
	ASSERT_EQUAL(ke::cleanTypeName("class struct SomeStruct typedef struct SomeStruct"), "SomeStruct SomeStruct");
	ASSERT_EQUAL(ke::cleanTypeName("enum class ke::Error"), "ke::Error");
}
*/





