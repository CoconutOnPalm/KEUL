#include <keul/keul.hpp>
#include <keul/unit-tests.hpp>


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
				
				ASSERT_EQUAL(ke::to_lower(oryginal), lower);
			}
		}
	}

	ASSERT_EQUAL(ke::to_lower("HELLO"), "hello");
	ASSERT_EQUAL(ke::to_lower("Hello"), "hello");
	ASSERT_EQUAL(ke::to_lower("hello"), "hello");
	ASSERT_EQUAL(ke::to_lower("hElLo"), "hello");
	ASSERT_EQUAL(ke::to_lower("HELLO WORLD"), "hello world");
	ASSERT_EQUAL(ke::to_lower("Hello World"), "hello world");
	ASSERT_EQUAL(ke::to_lower("hello world"), "hello world");
	ASSERT_EQUAL(ke::to_lower("123456"), "123456");
	ASSERT_EQUAL(ke::to_lower("Tesxt123With 123Numbers"), "tesxt123with 123numbers");
}
