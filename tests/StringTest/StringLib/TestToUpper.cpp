#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


class _ke_test_toUpper : public ke::test::_internal::TestBase {
public: _ke_test_toUpper() : ke::test::_internal::TestBase("toUpper") { } void Run() override; friend class TestManager;
}; struct _ke_test_toUpper_register_func_ptr_t {
	_ke_test_toUpper_register_func_ptr_t() {
		ke::test::_internal::TestManager::AddTest<_ke_test_toUpper>();
	} std::function<void()> callback;
}; static _ke_test_toUpper_register_func_ptr_t _ke_test_toUpper_register_func_ptr; void _ke_test_toUpper::Run()
{
	for (char c = 'a'; c < 'z'; c++)
	{
		for (char d = 'a'; d < 'z'; d++)
		{
			for (char e = 'a'; e < 'z'; e++)
			{
				std::string oryginal = { c, d, e };
				std::string upper = { static_cast<char>(c - 32), static_cast<char>(d - 32), static_cast<char>(e - 32) };

				ASSERT_EQUAL(ke::toUpper(oryginal), upper);
			}
		}
	}

	ASSERT_EQUAL(ke::toUpper("HELLO"), "HELLO");
	ASSERT_EQUAL(ke::toUpper("Hello"), "HELLO");
	ASSERT_EQUAL(ke::toUpper("hello"), "HELLO");
	ASSERT_EQUAL(ke::toUpper("hElLo"), "HELLO");
	ASSERT_EQUAL(ke::toUpper("HELLO WORLD"), "HELLO WORLD");
	ASSERT_EQUAL(ke::toUpper("Hello World"), "HELLO WORLD");
	ASSERT_EQUAL(ke::toUpper("hello world"), "HELLO WORLD");
	ASSERT_EQUAL(ke::toUpper("123456"), "123456");
	ASSERT_EQUAL(ke::toUpper("Tesxt123With 123Numbers"), "TESXT123WITH 123NUMBERS");
}