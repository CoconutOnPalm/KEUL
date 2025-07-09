#include <limits>

#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


#pragma init_seg(user)

KE_TEST(fromString)
{
	ASSERT_EQUAL(ke::fromString<int>("0").value(), 0);
	ASSERT_EQUAL(ke::fromString<int>("1").value(), 1);
	ASSERT_EQUAL(ke::fromString<int>("123").value(), 123);
	ASSERT_EQUAL(ke::fromString<int>("-123").value(), -123);
	ASSERT_EQUAL(ke::fromString<int>("1234567890").value(), 1234567890);
	ASSERT_EQUAL(ke::fromString<int>("-1234567890").value(), -1234567890);

	for (uint8_t i = 0; i < 255; i++)
	{
		ASSERT_EQUAL(ke::fromString<uint8_t>(ke::toString(i)).value(), i);
	}

	ASSERT_SIMILAR(ke::fromString<float>("0").value(), 0.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::fromString<float>("1").value(), 1.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::fromString<float>("1.5").value(), 1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::fromString<float>("-1.5").value(), -1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::fromString<float>("1.23457").value(), 1.23457f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::fromString<float>("-1.23457").value(), -1.23457f, std::numeric_limits<float>().epsilon());

	//ASSERT_ERROR(ke::fromString<int>("123.4"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<int>("123a"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::fromString<int>("a123"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<int>("123 4"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<int>(" 1234"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<int>("1234 "), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::fromString<int>("text"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::fromString<int>(""), ke::Error::InvalidArgument);

	//ASSERT_ERROR(ke::fromString<float>("123.4.5"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<float>("123a"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::fromString<float>("a123"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<float>("123 4"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<float>(" 1234"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::fromString<float>("1234 "), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::fromString<float>("text"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::fromString<float>(""), ke::Error::InvalidArgument);
}


KE_TEST(tryFromString)
{
	ASSERT_EQUAL(ke::tryFromString<int>("0", std::numeric_limits<int>::min()), 0);
	ASSERT_EQUAL(ke::tryFromString<int>("1", std::numeric_limits<int>::min()), 1);
	ASSERT_EQUAL(ke::tryFromString<int>("123", std::numeric_limits<int>::min()), 123);
	ASSERT_EQUAL(ke::tryFromString<int>("-123", std::numeric_limits<int>::min()), -123);
	ASSERT_EQUAL(ke::tryFromString<int>("1234567890", std::numeric_limits<int>::min()), 1234567890);
	ASSERT_EQUAL(ke::tryFromString<int>("-1234567890", std::numeric_limits<int>::min()), -1234567890);

	for (uint8_t i = 0; i < 255; i++)
	{
		ASSERT_EQUAL(ke::tryFromString<uint8_t>(ke::toString(i), std::numeric_limits<int>::min()), i);
	}

	ASSERT_SIMILAR(ke::tryFromString<float>("0", std::numeric_limits<float>::min()), 0.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::tryFromString<float>("1", std::numeric_limits<float>::min()), 1.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::tryFromString<float>("1.5", std::numeric_limits<float>::min()), 1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::tryFromString<float>("-1.5", std::numeric_limits<float>::min()), -1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::tryFromString<float>("1.23457", std::numeric_limits<float>::min()), 1.23457f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::tryFromString<float>("-1.23457", std::numeric_limits<float>::min()), -1.23457f, std::numeric_limits<float>().epsilon());

	ASSERT_EQUAL(ke::tryFromString<int>("a123", std::numeric_limits<int>::min()), std::numeric_limits<int>::min());
	ASSERT_EQUAL(ke::tryFromString<int>("text", std::numeric_limits<int>::min()), std::numeric_limits<int>::min());
	ASSERT_EQUAL(ke::tryFromString<int>("", std::numeric_limits<int>::min()), std::numeric_limits<int>::min());
	ASSERT_EQUAL(ke::tryFromString<float>("a123", 0.f), 0.f);
	ASSERT_EQUAL(ke::tryFromString<float>("text", 0.f), 0.f);
	ASSERT_EQUAL(ke::tryFromString<float>("", 0.f), 0.f);
}
