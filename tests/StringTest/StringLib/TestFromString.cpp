#include <limits>

#include <Utility.h>
#include <Testing.h>


#pragma init_seg(user)

KE_TEST(fromString)
{
	ASSERT_EQUAL(ke::fromString<int>("0").value(), 0);
	ASSERT_EQUAL(ke::fromString<int>("1").value(), 1);
	ASSERT_EQUAL(ke::fromString<int>("123").value(), 123);
	ASSERT_EQUAL(ke::fromString<int>("-123").value(), -123);
	ASSERT_EQUAL(ke::fromString<int>("1234567890").value(), 1234567890);
	ASSERT_EQUAL(ke::fromString<int>("-1234567890").value(), -1234567890);

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
