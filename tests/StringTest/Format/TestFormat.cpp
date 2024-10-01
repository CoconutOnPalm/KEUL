#include <Utility.h>
#include <Testing.h>

KE_TEST(format)
{
	const std::string reset_code = "\033[0m";
	ASSERT_EQUAL(ke::format("Hello {}!", "World"), "Hello World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [[]] {}!", "World"), "Hello [] World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [[[[]]]] {}!", "World"), "Hello [[]] World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [[[[[]]]] {}!", "World"), "Hello [[[]] World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [[[[]]]]] {}!", "World"), "Hello [[]]] World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [[[0]]] {}!", "World"), "Hello [\033[0m] World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [2137] {}!", "World"), "Hello [2137] World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [rgb(255, 0, 0)] {}!", "World"), "Hello \033[38;2;255;0;0m World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [rgb(255,0,0)] {}!", "World"), "Hello \033[38;2;255;0;0m World!" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [ World"), "Hello [ World" + reset_code);
	ASSERT_EQUAL(ke::format("Hello ] World"), "Hello ] World" + reset_code);
	ASSERT_EQUAL(ke::format("Hello [] World"), "Hello [] World" + reset_code);

	ASSERT_EQUAL(ke::format_no_ansi("Hello {}!", "World"), "Hello World!");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [[]] {}!", "World"), "Hello [] World!");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [[[[]]]] {}!", "World"), "Hello [[]] World!");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [[[0]]] {}!", "World"), "Hello [] World!");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [2137] {}!", "World"), "Hello [2137] World!");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [rgb(255, 0, 0)] {}!", "World"), "Hello  World!");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [rgb(255,0,0)] {}!", "World"), "Hello  World!");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [ World"), "Hello [ World");
	ASSERT_EQUAL(ke::format_no_ansi("Hello ] World"), "Hello ] World");
	ASSERT_EQUAL(ke::format_no_ansi("Hello [] World"), "Hello [] World");
}
