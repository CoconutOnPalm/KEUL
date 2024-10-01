#include <array>

#include <Utility.h>
#include <Testing.h>
#include <ranges>


KE_TEST(splitString_vector)
{
	const std::vector<std::string> words = { "Lorem", "ipsum", "dolor", "sit", "amet" };

	KE_ASSERT(words.size() == 5);

	std::vector<std::function<std::string(char)>> builders;

	builders.push_back([&words](char split_char) {
		return split_char + words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4] + split_char;
		});

	builders.push_back([&words](char split_char) {
		return words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4] + split_char;
		});

	builders.push_back([&words](char split_char) {
		return split_char + words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4];
		});

	builders.push_back([&words](char split_char) {
		return words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4];
		});


	for (char c = '!'; c <= '/'; c++)
	{
		for (auto& create_string : builders)
		{
			std::vector<std::string> result_vec = ke::splitString<std::vector>(create_string(c), c);
			ASSERT_EQUAL(result_vec, words);
		}
	}
}