#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


KE_TEST(toLower)
{
	for (char c = 'A'; c < 'Z'; c++)
	{
		for (char d = 'A'; d < 'Z'; d++)
		{
			for (char e = 'A'; e < 'Z'; e++)
			{
				std::string oryginal = { c, d, e };
				std::string lower = { static_cast<char>(c + 32), static_cast<char>(d + 32), static_cast<char>(e + 32) };
				
				ASSERT_EQUAL(ke::toLower(oryginal), lower);
			}
		}
	}

	ASSERT_EQUAL(ke::toLower("HELLO"), "hello");
	ASSERT_EQUAL(ke::toLower("Hello"), "hello");
	ASSERT_EQUAL(ke::toLower("hello"), "hello");
	ASSERT_EQUAL(ke::toLower("hElLo"), "hello");
	ASSERT_EQUAL(ke::toLower("HELLO WORLD"), "hello world");
	ASSERT_EQUAL(ke::toLower("Hello World"), "hello world");
	ASSERT_EQUAL(ke::toLower("hello world"), "hello world");
	ASSERT_EQUAL(ke::toLower("123456"), "123456");
	ASSERT_EQUAL(ke::toLower("Tesxt123With 123Numbers"), "tesxt123with 123numbers");
}
