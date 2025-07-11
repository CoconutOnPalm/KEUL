#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


int max(int a, int b, int c)
{
    // BUG: Fails when c is the largest value
    if (a > b)
        return (a > c) ? a : b; // change to: (a > c) ? a : c
    else
        return (b > c) ? b : c;
}


struct Vec2 { float x, y; };

Vec2 normalize(const Vec2& vec)
{
    float norm = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    return Vec2{
        .x = vec.x / norm,
        .y = vec.y / norm,
    };
}


std::expected<int, ke::Error> error_prone_function(const int x)
{
    if (x < 0)
        return std::unexpected(ke::Error::InvalidArgument);

    return x;
}


KE_TEST(max_test)
{
    ASSERT_EQUAL(max(1, 2, 3), 3); // fail
    ASSERT_EQUAL(max(1, 3, 2), 3);
    ASSERT_EQUAL(max(2, 1, 3), 3); // fail
    ASSERT_EQUAL(max(2, 3, 1), 3);
    ASSERT_EQUAL(max(3, 1, 2), 3);
    ASSERT_EQUAL(max(3, 2, 1), 3);

    ASSERT_EQUAL(max(0, 0, 0), 0);
}

KE_TEST(normalize_test)
{
    ASSERT_SIMILAR(normalize({ 3, 2 }).x, 0.27735 * 3, 0.00001);
    ASSERT_SIMILAR(normalize({ 3, 2 }).y, 0.27735 * 2, 0.00001);
}

KE_TEST(error_prone_function_test)
{
    for (int i = 0; i <= 1000; i++)
        ASSERT_EQUAL(error_prone_function(i), i);

    for (int i = -1000; i < 0; i++)
        ASSERT_ERROR(error_prone_function(i), ke::Error::InvalidArgument);
}


int main()
{
	KE_RUN_ALL_TESTS();
}
