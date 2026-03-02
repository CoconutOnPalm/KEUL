#include <limits>

#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


#pragma init_seg(user)

KE_TEST(fromString)
{
	ASSERT_EQUAL(ke::from_string<int>("0").value(), 0);
	ASSERT_EQUAL(ke::from_string<int>("1").value(), 1);
	ASSERT_EQUAL(ke::from_string<int>("123").value(), 123);
	ASSERT_EQUAL(ke::from_string<int>("-123").value(), -123);
	ASSERT_EQUAL(ke::from_string<int>("1234567890").value(), 1234567890);
	ASSERT_EQUAL(ke::from_string<int>("-1234567890").value(), -1234567890);

	for (uint8_t i = 0; i < 255; i++)
	{
		ASSERT_EQUAL(ke::from_string<uint8_t>(ke::to_string(i)).value(), i);
	}

	ASSERT_SIMILAR(ke::from_string<float>("0").value(), 0.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string<float>("1").value(), 1.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string<float>("1.5").value(), 1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string<float>("-1.5").value(), -1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string<float>("1.23457").value(), 1.23457f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string<float>("-1.23457").value(), -1.23457f, std::numeric_limits<float>().epsilon());

	//ASSERT_ERROR(ke::from_string<int>("123.4"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<int>("123a"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::from_string<int>("a123"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<int>("123 4"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<int>(" 1234"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<int>("1234 "), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::from_string<int>("text"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::from_string<int>(""), ke::Error::InvalidArgument);

	//ASSERT_ERROR(ke::from_string<float>("123.4.5"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<float>("123a"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::from_string<float>("a123"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<float>("123 4"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<float>(" 1234"), ke::Error::InvalidArgument);
	//ASSERT_ERROR(ke::from_string<float>("1234 "), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::from_string<float>("text"), ke::Error::InvalidArgument);
	ASSERT_ERROR(ke::from_string<float>(""), ke::Error::InvalidArgument);
}


KE_TEST(fromStringOr)
{
	ASSERT_EQUAL(ke::from_string_or<int>("0", std::numeric_limits<int>::min()), 0);
	ASSERT_EQUAL(ke::from_string_or<int>("1", std::numeric_limits<int>::min()), 1);
	ASSERT_EQUAL(ke::from_string_or<int>("123", std::numeric_limits<int>::min()), 123);
	ASSERT_EQUAL(ke::from_string_or<int>("-123", std::numeric_limits<int>::min()), -123);
	ASSERT_EQUAL(ke::from_string_or<int>("1234567890", std::numeric_limits<int>::min()), 1234567890);
	ASSERT_EQUAL(ke::from_string_or<int>("-1234567890", std::numeric_limits<int>::min()), -1234567890);

	for (uint8_t i = 0; i < 255; i++)
	{
		ASSERT_EQUAL(ke::from_string_or<uint8_t>(ke::to_string(i), std::numeric_limits<uint8_t>::min()), i);
	}

	ASSERT_SIMILAR(ke::from_string_or<float>("0", std::numeric_limits<float>::min()), 0.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string_or<float>("1", std::numeric_limits<float>::min()), 1.0f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string_or<float>("1.5", std::numeric_limits<float>::min()), 1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string_or<float>("-1.5", std::numeric_limits<float>::min()), -1.5f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string_or<float>("1.23457", std::numeric_limits<float>::min()), 1.23457f, std::numeric_limits<float>().epsilon());
	ASSERT_SIMILAR(ke::from_string_or<float>("-1.23457", std::numeric_limits<float>::min()), -1.23457f, std::numeric_limits<float>().epsilon());

	ASSERT_EQUAL(ke::from_string_or<int>("a123", std::numeric_limits<int>::min()), std::numeric_limits<int>::min());
	ASSERT_EQUAL(ke::from_string_or<int>("text", std::numeric_limits<int>::min()), std::numeric_limits<int>::min());
	ASSERT_EQUAL(ke::from_string_or<int>("", std::numeric_limits<int>::min()), std::numeric_limits<int>::min());
	ASSERT_EQUAL(ke::from_string_or<float>("a123", 0.f), 0.f);
	ASSERT_EQUAL(ke::from_string_or<float>("text", 0.f), 0.f);
	ASSERT_EQUAL(ke::from_string_or<float>("", 0.f), 0.f);
}
