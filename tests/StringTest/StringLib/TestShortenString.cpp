#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


KE_TEST(shortenString)
{
	ASSERT_EQUAL(ke::shortenString("Hello World", 5), "He...");
	ASSERT_EQUAL(ke::shortenString("Hello World", 11), "Hello World");
	ASSERT_EQUAL(ke::shortenString("Hello World", 12), "Hello World");
	ASSERT_EQUAL(ke::shortenString("Hello World", 9), "Hello ...");
	ASSERT_EQUAL(ke::shortenString("Hello World", 8), "Hello...");
	ASSERT_EQUAL(ke::shortenString("Hello World", 0), "");
	ASSERT_EQUAL(ke::shortenString("Hello World", 1), ".");
	ASSERT_EQUAL(ke::shortenString("Hello World", 2), "..");
	ASSERT_EQUAL(ke::shortenString("Hello World", 3), "...");
	ASSERT_EQUAL(ke::shortenString("Hello World", 4), "H...");

	ASSERT_EQUAL(ke::shortenString("aaa", 3), "aaa");
	ASSERT_EQUAL(ke::shortenString("aaa", 2), "..");
	ASSERT_EQUAL(ke::shortenString("aaa", 1), ".");
	ASSERT_EQUAL(ke::shortenString("aaa", 0), "");

	ASSERT_EQUAL(ke::shortenString("a", 1), "a");
	ASSERT_EQUAL(ke::shortenString("a", 0), "");
	ASSERT_EQUAL(ke::shortenString("a", 2), "a");
	ASSERT_EQUAL(ke::shortenString("a", 3), "a");

	ASSERT_EQUAL(ke::shortenString("", 0), "");
	ASSERT_EQUAL(ke::shortenString("", 1), "");
	ASSERT_EQUAL(ke::shortenString("", 2), "");

	ASSERT_EQUAL(ke::shortenString("aaaa", 0), "");
	ASSERT_EQUAL(ke::shortenString("aaaa", 1), ".");
	ASSERT_EQUAL(ke::shortenString("aaaa", 2), "..");
	ASSERT_EQUAL(ke::shortenString("aaaa", 3), "...");
	ASSERT_EQUAL(ke::shortenString("aaaa", 4), "aaaa");
	ASSERT_EQUAL(ke::shortenString("aaaa", 5), "aaaa");
	ASSERT_EQUAL(ke::shortenString("aaaa", 6), "aaaa");
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





