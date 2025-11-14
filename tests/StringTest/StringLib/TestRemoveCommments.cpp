#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>


KE_TEST(removeComments)
{
	// more like a check, not a test

	std::string test_string1 = R""""(
			// This is a comment
			Hello World;// This is a comment
			
			@ not a comment
			// This is a comment
			)"""";


	std::string test_string2 = R""""(
			# This is a comment
			Hello World;# This is a comment
			
			@ not a comment
			# This is a comment
			)"""";

	std::string expected_string = R""""(
			
			Hello World;
			
			@ not a comment
			
			)"""";

	ASSERT_EQUAL(ke::removeComments(test_string1), expected_string);
	ASSERT_EQUAL(ke::removeComments(test_string2, "#"), expected_string);
}