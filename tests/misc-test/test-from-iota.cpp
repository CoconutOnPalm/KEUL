#include <keul/keul.hpp>
#include <keul/unit-tests.hpp>


KE_TEST(FromIOTA_test)
{
	std::vector<int> _0_10{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	ASSERT_EQUAL(ke::iota_to_vec<int>(0, 10), _0_10);

	std::vector<int> _0_0{};
	ASSERT_EQUAL(ke::iota_to_vec<int>(0, 0), _0_0);

	std::vector<int> _10_0{};
	ASSERT_EQUAL(ke::iota_to_vec<int>(10, 0), _10_0);
}