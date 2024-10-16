#include <Testing.h>


KE_TEST(stdVector_formatter)
{
    ASSERT_EQUAL(std::format("{}", std::vector<int>{}), "[]");
    ASSERT_EQUAL(std::format("{}", std::vector{1, 2, 3}), "[1, 2, 3]");
    ASSERT_EQUAL(std::format("{}", std::vector{"Hello", "World"}), "[Hello, World]");
    ASSERT_EQUAL(std::format("{}", std::vector{'a', 'b', 'c'}), "[a, b, c]");
    ASSERT_EQUAL(std::format("{}", std::vector{1.0f, 2.0f, 3.0f}), "[1.000000, 2.000000, 3.000000]");
}


KE_TEST(stdArray_formatter)
{
    ASSERT_EQUAL(std::format("{}", std::array<int, 0>{}), "[]");
    ASSERT_EQUAL(std::format("{}", std::array{1, 2, 3}), "[1, 2, 3]");
    ASSERT_EQUAL(std::format("{}", std::array{"Hello", "World"}), "[Hello, World]");
    ASSERT_EQUAL(std::format("{}", std::array{'a', 'b', 'c'}), "[a, b, c]");
    ASSERT_EQUAL(std::format("{}", std::array{1.0f, 2.0f, 3.0f}), "[1.000000, 2.000000, 3.000000]");
}


KE_TEST(stdPair_formatter)
{
    ASSERT_EQUAL(std::format("{}", std::pair{1, 2}), "(1, 2)");
    ASSERT_EQUAL(std::format("{}", std::pair{1.0f, 2.0f}), "(1.000000, 2.000000)");
    ASSERT_EQUAL(std::format("{}", std::pair{"Hello", "World"}), "(Hello, World)");
    ASSERT_EQUAL(std::format("{}", std::pair{'a', 'b'}), "(a, b)");
}