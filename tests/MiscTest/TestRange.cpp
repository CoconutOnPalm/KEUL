#include <Utility.h>
#include <Testing.h>


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
	ASSERT_TRUE(ke::InRange(ke::OpenRange(-2, 2), 0));
	ASSERT_FALSE(ke::InRange(ke::OpenRange(-2, 2), 2));
	ASSERT_FALSE(ke::InRange(ke::OpenRange(-2, 2), -2));

	ASSERT_TRUE(ke::InRange(ke::ClosedRange(-2, 2), 0));
	ASSERT_TRUE(ke::InRange(ke::ClosedRange(-2, 2), 2));
	ASSERT_TRUE(ke::InRange(ke::ClosedRange(-2, 2), -2));

	ASSERT_TRUE(ke::InRange(ke::HalfOpenRange(-2, 2), 0));
	ASSERT_FALSE(ke::InRange(ke::HalfOpenRange(-2, 2), 2));
	ASSERT_TRUE(ke::InRange(ke::HalfOpenRange(-2, 2), -2));
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

