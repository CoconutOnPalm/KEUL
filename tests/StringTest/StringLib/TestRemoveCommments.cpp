#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


KE_TEST(removeComments)
{
	// more like a check, not a test

	std::string test_string = R""""(
			// This is a comment
			Hello World;// This is a comment
			
			# not a comment
			// This is a comment
			)"""";

	std::string expected_string = R""""(
			
			Hello World;
			
			# not a comment
			
			)"""";

	ASSERT_EQUAL(ke::removeComments(test_string), expected_string);
}