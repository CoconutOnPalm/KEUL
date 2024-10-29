#include <array>

#include <Utility.h>
#include <Testing.h>
#include <ranges>


KE_TEST(splitString_vector)
{
	const std::vector<std::string> words = { "Lorem", "ipsum", "dolor", "sit", "amet" };

	KE_ASSERT(words.size() == 5);

	std::vector<std::function<std::string(char)>> builders;

	// "split" <word> "split" <word> "split" <word> "split" <word> "split" <word> "split"
	builders.push_back([&words](char split_char) {
		return split_char + words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4] + split_char;
		});

	// <word> "split" <word> "split" <word> "split" <word> "split" <word> "split"
	builders.push_back([&words](char split_char) {
		return words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4] + split_char;
		});

	// "split" <word> "split" <word> "split" <word> "split" <word> "split" <word>
	builders.push_back([&words](char split_char) {
		return split_char + words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4];
		});

	// <word> "split" <word> "split" <word> "split" <word> "split" <word>
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


	std::vector<std::function<std::string(std::string)>> multichar_builders;

	// "split" <word> "split" <word> "split" <word> "split" <word> "split" <word> "split"
	multichar_builders.push_back([&words](std::string split_str) {
		return split_str + words[0] + split_str + words[1] + split_str + words[2] + split_str + words[3] + split_str + words[4] + split_str;
		});

	// <word> "split" <word> "split" <word> "split" <word> "split" <word> "split"
	multichar_builders.push_back([&words](std::string split_str) {
		return words[0] + split_str + words[1] + split_str + words[2] + split_str + words[3] + split_str + words[4] + split_str;
		});

	// "split" <word> "split" <word> "split" <word> "split" <word> "split" <word>
	multichar_builders.push_back([&words](std::string split_str) {
		return split_str + words[0] + split_str + words[1] + split_str + words[2] + split_str + words[3] + split_str + words[4];
		});

	// <word> "split" <word> "split" <word> "split" <word> "split" <word>
	multichar_builders.push_back([&words](std::string split_str) {
		return words[0] + split_str + words[1] + split_str + words[2] + split_str + words[3] + split_str + words[4];
		});

	for (char c = '!'; c <= '/' - 5; c++)
	{
		for (auto& create_string : multichar_builders)
		{
			std::string split_str = { c, ++c, ++c, ++c, ++c };
			std::println("Split string: ", split_str);
			std::vector<std::string> result_vec = ke::splitString<std::vector>(create_string(split_str), split_str);
			std::println("Result: ", result_vec);
			ASSERT_EQUAL(result_vec, words);
		}
	}

	ASSERT_EQUAL(ke::splitString<std::vector>("1Lorem2ipsum3dolor4sit5amet6", "1", "2", "3", "4", "5", "6"), words);

	ASSERT_EQUAL(ke::splitString<std::vector>("#..#...#.3.#..1#.#..#..#2#..23#..", "#..", "2", "3"), 
		std::vector<std::string>({ ".#.", ".", "1#.", "#" }));

	ASSERT_EQUAL(ke::splitString<std::vector>("#..#..#", "#.........."), std::vector<std::string>({ "#..#..#" }));
	ASSERT_EQUAL(ke::splitString<std::vector>("#..#..#", "#", "#"), std::vector<std::string>({ "..", ".." }));
}


KE_TEST(splitString_set)
{
	const std::vector<std::string> words = { "Lorem", "ipsum", "dolor", "sit", "amet" };
	const std::set<std::string> words_set(words.begin(), words.end());

	KE_ASSERT(words.size() == 5);

	std::vector<std::function<std::string(char)>> builders;

	// "split" <word> "split" <word> "split" <word> "split" <word> "split" <word> "split"
	builders.push_back([&words](char split_char) {
		return split_char + words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4] + split_char;
		});

	// <word> "split" <word> "split" <word> "split" <word> "split" <word> "split"
	builders.push_back([&words](char split_char) {
		return words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4] + split_char;
		});

	// "split" <word> "split" <word> "split" <word> "split" <word> "split" <word>
	builders.push_back([&words](char split_char) {
		return split_char + words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4];
		});

	// <word> "split" <word> "split" <word> "split" <word> "split" <word>
	builders.push_back([&words](char split_char) {
		return words[0] + split_char + words[1] + split_char + words[2] + split_char + words[3] + split_char + words[4];
		});

	for (char c = '!'; c <= '/'; c++)
	{
		for (auto& create_string : builders)
		{
			std::set<std::string> result_set = ke::splitString<std::set>(create_string(c), c);
			ASSERT_EQUAL(result_set, words_set);
		}
	}

	ASSERT_EQUAL(ke::splitString<std::set>("1Lorem2ipsum3dolor4sit5amet6", "1", "2", "3", "4", "5", "6"), words_set);

	ASSERT_EQUAL(ke::splitString<std::set>("#..#...#.3.#..1#.#..#..#2#..23#..#", "#..", "2", "3"), 
		std::set<std::string>({ ".#.", ".", "1#.", "#" }));

	ASSERT_EQUAL(ke::splitString<std::set>("#..#..#", "#.........."), std::set<std::string>({ "#..#..#" }));
	ASSERT_EQUAL(ke::splitString<std::set>("#..#..#", "#", "#"), std::set<std::string>({ "..", ".." }));

}


KE_TEST(splitString_pair)
{
	std::map<std::string, std::function<std::string(char)>> builders;

	// left "split" right
	builders.emplace("SPLIT", [](char split_char) {
		return std::string("left") + split_char + "right";
		});

	// left right
	builders.emplace("MERGED", [](char split_char) {
		return std::string("left") + "right";
		});

	// "split" left right
	builders.emplace("LEFT_EMPTY", [](char split_char) {
		return split_char + std::string("left") + "right";
		});

	// left right "split"
	builders.emplace("RIGHT_EMPTY", [](char split_char) {
		return std::string("left") + "right" + split_char;
		});

	std::map<std::string, std::pair<std::string, std::string>> expected_results;
	expected_results["SPLIT"] = { "left", "right" };
	expected_results["MERGED"] = { "leftright", "" };
	expected_results["LEFT_EMPTY"] = { "", "leftright" };
	expected_results["RIGHT_EMPTY"] = { "leftright", "" };

	for (char c = '!'; c <= '/'; c++)
	{
		for (auto& [name, create_string] : builders)
		{
			std::pair<std::string, std::string> result_pair = ke::splitStringToPair<std::pair>(create_string(c), c);
			ASSERT_EQUAL(result_pair, expected_results[name]);
		}
	}
}