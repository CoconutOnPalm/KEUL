#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


KE_TEST(OpenRange)
{
	ke::OpenRange<int> rangei(1, 10);
	ke::OpenRange<float> rangef(1.0f, 10.0f);
	ke::OpenRange<char> rangec('a', 'z');
	//ke::OpenRange<std::string> ranges("a", "z");

	ASSERT_TRUE(ke::OpenRange<int>(1, 1).isDegenerate());
	ASSERT_TRUE(ke::OpenRange<float>(1.0f, 1.0f).isDegenerate());
	ASSERT_TRUE(ke::OpenRange<char>('a', 'a').isDegenerate());
	//ASSERT_TRUE(ke::OpenRange<std::string>("a", "a").isDegenerate());
	ASSERT_TRUE(ke::OpenRange<uint8_t>(-1, 1).isDegenerate());

	ASSERT_FALSE(rangei.isDegenerate());
	ASSERT_FALSE(rangef.isDegenerate());
	ASSERT_FALSE(rangec.isDegenerate());
	//ASSERT_FALSE(ranges.isDegenerate());

	ASSERT_TRUE(rangei.contains(5));
	ASSERT_TRUE(rangef.contains(5.0f));
	ASSERT_TRUE(rangec.contains('f'));
	//ASSERT_TRUE(ranges.contains("f"));

	ASSERT_FALSE(rangei.contains(10));
	ASSERT_FALSE(rangef.contains(10.0f));
	ASSERT_FALSE(rangec.contains('z'));
	//ASSERT_FALSE(ranges.contains("z"));

	ASSERT_FALSE(rangei.contains(1));
	ASSERT_FALSE(rangef.contains(1.0f));
	ASSERT_FALSE(rangec.contains('a'));
	//ASSERT_FALSE(ranges.contains("a"));

	ASSERT_FALSE(rangei.contains(0));
	ASSERT_FALSE(rangef.contains(0.0f));
	ASSERT_FALSE(rangec.contains('`'));
	//ASSERT_FALSE(ranges.contains("`"));

	ASSERT_FALSE(rangei.contains(11));
	ASSERT_FALSE(rangef.contains(11.0f));
	ASSERT_FALSE(rangec.contains('{'));
	//ASSERT_FALSE(ranges.contains("{"));

	ASSERT_FALSE(ke::OpenRange<uint8_t>(-1, 1).contains(0));
	ASSERT_FALSE(ke::OpenRange<uint8_t>(-1, 1).contains(2));
	ASSERT_FALSE(ke::OpenRange<uint8_t>(-1, 1).contains(-2));
	ASSERT_FALSE(ke::OpenRange<uint8_t>(-1, 1).contains(1));
	ASSERT_FALSE(ke::OpenRange<uint8_t>(-1, 1).contains(-1));
}


KE_TEST(ClosedRange)
{
	ke::ClosedRange<int> rangei(1, 10);
	ke::ClosedRange<float> rangef(1.0f, 10.0f);
	ke::ClosedRange<char> rangec('a', 'z');
	//ke::ClosedRange<std::string> ranges("a", "z");

	//ASSERT_TRUE(ke::ClosedRange<std::string>("a", "a").isDegenerate());
	ASSERT_TRUE(ke::ClosedRange<uint8_t>(-1, 1).isDegenerate());

	ASSERT_FALSE(rangei.isDegenerate());
	ASSERT_FALSE(rangef.isDegenerate());
	ASSERT_FALSE(rangec.isDegenerate());
	//ASSERT_FALSE(ranges.isDegenerate());

	ASSERT_TRUE(rangei.contains(5));
	ASSERT_TRUE(rangef.contains(5.0f));
	ASSERT_TRUE(rangec.contains('f'));
	//ASSERT_TRUE(ranges.contains("f"));

	ASSERT_TRUE(rangei.contains(10));
	ASSERT_TRUE(rangef.contains(10.0f));
	ASSERT_TRUE(rangec.contains('z'));
	//ASSERT_TRUE(ranges.contains("z"));

	ASSERT_TRUE(rangei.contains(1));
	ASSERT_TRUE(rangef.contains(1.0f));
	ASSERT_TRUE(rangec.contains('a'));
	//ASSERT_TRUE(ranges.contains("a"));

	ASSERT_FALSE(rangei.contains(0));
	ASSERT_FALSE(rangef.contains(0.0f));
	ASSERT_FALSE(rangec.contains('`'));
	//ASSERT_FALSE(ranges.contains("`"));

	ASSERT_FALSE(rangei.contains(11));
	ASSERT_FALSE(rangef.contains(11.0f));
	ASSERT_FALSE(rangec.contains('{'));
	//ASSERT_FALSE(ranges.contains("{"));

	ASSERT_FALSE(ke::ClosedRange<uint8_t>(-1, 1).contains(0));
	ASSERT_FALSE(ke::ClosedRange<uint8_t>(-1, 1).contains(2));
	ASSERT_FALSE(ke::ClosedRange<uint8_t>(-1, 1).contains(-2));
	ASSERT_FALSE(ke::ClosedRange<uint8_t>(-1, 1).contains(1));
	ASSERT_FALSE(ke::ClosedRange<uint8_t>(-1, 1).contains(-1));
}


KE_TEST(HalfOpenRange)
{
	ke::HalfOpenRange<int> rangei(1, 10);
	ke::HalfOpenRange<float> rangef(1.0f, 10.0f);
	ke::HalfOpenRange<char> rangec('a', 'z');
	//ke::HalfOpenRange<std::string> ranges("a", "z");

	ASSERT_TRUE(ke::HalfOpenRange<int>(1, 1).isDegenerate());
	ASSERT_TRUE(ke::HalfOpenRange<float>(1.0f, 1.0f).isDegenerate());
	ASSERT_TRUE(ke::HalfOpenRange<char>('a', 'a').isDegenerate());
	//ASSERT_TRUE(ke::HalfOpenRange<std::string>("a", "a").isDegenerate());
	ASSERT_TRUE(ke::HalfOpenRange<uint8_t>(-1, 1).isDegenerate());

	ASSERT_FALSE(rangei.isDegenerate());
	ASSERT_FALSE(rangef.isDegenerate());
	ASSERT_FALSE(rangec.isDegenerate());
	//ASSERT_FALSE(ranges.isDegenerate());

	ASSERT_TRUE(rangei.contains(5));
	ASSERT_TRUE(rangef.contains(5.0f));
	ASSERT_TRUE(rangec.contains('f'));
	//ASSERT_TRUE(ranges.contains("f"));

	ASSERT_FALSE(rangei.contains(10));
	ASSERT_FALSE(rangef.contains(10.0f));
	ASSERT_FALSE(rangec.contains('z'));
	//ASSERT_FALSE(ranges.contains("z"));

	ASSERT_TRUE(rangei.contains(1));
	ASSERT_TRUE(rangef.contains(1.0f));
	ASSERT_TRUE(rangec.contains('a'));
	//ASSERT_TRUE(ranges.contains("a"));

	ASSERT_FALSE(rangei.contains(0));
	ASSERT_FALSE(rangef.contains(0.0f));
	ASSERT_FALSE(rangec.contains('`'));
	//ASSERT_FALSE(ranges.contains("`"));

	ASSERT_FALSE(rangei.contains(11));
	ASSERT_FALSE(rangef.contains(11.0f));
	ASSERT_FALSE(rangec.contains('{'));
	//ASSERT_FALSE(ranges.contains("{"));

	ASSERT_FALSE(ke::HalfOpenRange<uint8_t>(-1, 1).contains(0));
	ASSERT_FALSE(ke::HalfOpenRange<uint8_t>(-1, 1).contains(2));
	ASSERT_FALSE(ke::HalfOpenRange<uint8_t>(-1, 1).contains(-2));
	ASSERT_FALSE(ke::HalfOpenRange<uint8_t>(-1, 1).contains(1));
	ASSERT_FALSE(ke::HalfOpenRange<uint8_t>(-1, 1).contains(-1));
}


KE_TEST(inRange)
{
	ASSERT_TRUE(ke::inRange(ke::OpenRange(-2, 2), 0));
	ASSERT_FALSE(ke::inRange(ke::OpenRange(-2, 2), 2));
	ASSERT_FALSE(ke::inRange(ke::OpenRange(-2, 2), -2));

	ASSERT_TRUE(ke::inRange(ke::ClosedRange(-2, 2), 0));
	ASSERT_TRUE(ke::inRange(ke::ClosedRange(-2, 2), 2));
	ASSERT_TRUE(ke::inRange(ke::ClosedRange(-2, 2), -2));

	ASSERT_TRUE(ke::inRange(ke::HalfOpenRange(-2, 2), 0));
	ASSERT_FALSE(ke::inRange(ke::HalfOpenRange(-2, 2), 2));
	ASSERT_TRUE(ke::inRange(ke::HalfOpenRange(-2, 2), -2));
}


KE_TEST(restrainVariable)
{
	int a = 0;
	ASSERT_TRUE(ke::restrainVariable(a, 1, 10));
	ASSERT_EQUAL(a, 1);

	a = 0;
	ASSERT_TRUE(ke::restrainVariable(a, -10, -1));
	ASSERT_EQUAL(a, -1);

	a = 0;
	ASSERT_FALSE(ke::restrainVariable(a, 0, 0));
	ASSERT_EQUAL(a, 0);

	a = 0;
	ASSERT_FALSE(ke::restrainVariable(a, 0, 0));
	ASSERT_EQUAL(a, 0);

	// degenerate range
	a = 4;
	ASSERT_FALSE(ke::restrainVariable(a, 10, -10));
	ASSERT_EQUAL(a, 4);

	a = 0;
	ASSERT_TRUE(ke::restrainVariable(a, ke::ClosedRange(1, 10)));
	ASSERT_EQUAL(a, 1);

	a = 0;
	ASSERT_FALSE(ke::restrainVariable(a, ke::ClosedRange(0, 10)));
	ASSERT_EQUAL(a, 0);

	a = 0;
	ASSERT_FALSE(ke::restrainVariable(a, ke::ClosedRange(0, 0)));
	ASSERT_EQUAL(a, 0);

	a = 0;
	ASSERT_FALSE(ke::restrainVariable(a, ke::ClosedRange(0, 0)));
	ASSERT_EQUAL(a, 0);

	ke::Random generator(0);

	for (int i = 0; i < 100; i++)
	{
		int a = generator.Int32(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
		ke::restrainVariable(a, ke::ClosedRange(0, 100));
		ASSERT_TRUE(ke::inRange(ke::ClosedRange(0, 100), a));
	}

	for (char c = 'a'; c <= 'z'; c++)
	{
		char a = c;
		ke::restrainVariable(a, ke::ClosedRange('a', 'z'));
		ASSERT_EQUAL(a, c);
	}
	
	for (char c = ' '; c <= '~'; c++)
	{
		char a = c;
		ke::restrainVariable(a, ke::ClosedRange('a', 'z'));
		ASSERT_TRUE(ke::inRange(ke::ClosedRange('a', 'z'), a));
	}

	for (float f = -100.0f; f <= 100.0f; f += 0.1f)
	{
		float a = f;
		ke::restrainVariable(a, ke::ClosedRange(-10.0f, 10.0f));
		ASSERT_TRUE(ke::inRange(ke::ClosedRange(-10.0f, 10.0f), a));
	}
}


KE_TEST(RangeOperators)
{
	ke::OpenRange<int> rangei(1, 10);
	ke::OpenRange<float> rangef(1.0f, 10.0f);
	ke::OpenRange<char> rangec('a', 'z');
	//ke::OpenRange<std::string> ranges("a", "z");

	ASSERT_TRUE(rangei == ke::OpenRange<int>(1, 10));
	ASSERT_TRUE(rangef == ke::OpenRange<float>(1.0f, 10.0f));
	ASSERT_TRUE(rangec == ke::OpenRange<char>('a', 'z'));
	ASSERT_TRUE(rangei == ke::ClosedRange<int>(1, 10));
	//ASSERT_TRUE(ranges == ke::OpenRange<std::string>("a", "z"));

	ASSERT_FALSE(rangei != ke::OpenRange<int>(1, 10));
	ASSERT_FALSE(rangef != ke::OpenRange<float>(1.0f, 10.0f));
	ASSERT_FALSE(rangec != ke::OpenRange<char>('a', 'z'));
	ASSERT_FALSE(rangei != ke::ClosedRange<int>(1, 10));
	//ASSERT_FALSE(ranges != ke::OpenRange<std::string>("a", "z"));

	ASSERT_FALSE(rangei == ke::OpenRange<int>(1, 11));
	ASSERT_FALSE(rangef == ke::OpenRange<float>(1.0f, 11.0f));
	ASSERT_FALSE(rangec == ke::OpenRange<char>('a', 'y'));
	//ASSERT_FALSE(ranges == ke::OpenRange<std::string>("a", "y"));

	ASSERT_TRUE(rangei != ke::OpenRange<int>(1, 11));
	ASSERT_TRUE(rangef != ke::OpenRange<float>(1.0f, 11.0f));
	ASSERT_TRUE(rangec != ke::OpenRange<char>('a', 'y'));
	//ASSERT_TRUE(ranges != ke::OpenRange<std::string>("a", "y"));
}

