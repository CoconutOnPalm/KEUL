#include <array>

#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>
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
			std::vector<std::string> result_vec = ke::splitString<std::vector>(create_string(split_str), { split_str });
			ASSERT_EQUAL(result_vec, words);
		}
	}

	ASSERT_EQUAL(ke::splitString<std::vector>("1Lorem2ipsum3dolor4sit5amet6", { "1", "2", "3", "4", "5", "6" }), words);

	ASSERT_EQUAL(ke::splitString<std::vector>("#..#...#.3.#..1#.#..#..#2#..23#..", { "#..", "2", "3" }),
		std::vector<std::string>({ ".#.", ".", "1#.", "#" }));

	ASSERT_EQUAL(ke::splitString<std::vector>("#..#..#", { "#.........." }), std::vector<std::string>({ "#..#..#" }));
	ASSERT_EQUAL(ke::splitString<std::vector>("#..#..#", { "#", "#" }), std::vector<std::string>({ "..", ".." }));
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

	ASSERT_EQUAL(ke::splitString<std::set>("1Lorem2ipsum3dolor4sit5amet6", { "1", "2", "3", "4", "5", "6" }), words_set);

	ASSERT_EQUAL(ke::splitString<std::set>("#..#...#.3.#..1#.#..#..#2#..23#..#", { "#..", "2", "3" }),
		std::set<std::string>({ ".#.", ".", "1#.", "#" }));

	ASSERT_EQUAL(ke::splitString<std::set>("#..#..#", { "#.........." }), std::set<std::string>({ "#..#..#" }));
	ASSERT_EQUAL(ke::splitString<std::set>("#..#..#", { "#", "#" }), std::set<std::string>({ "..", ".." }));

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
			std::pair<std::string, std::string> result_pair = ke::splitStringToPair(create_string(c), c, 0);
			ASSERT_EQUAL(result_pair, expected_results[name]);
		}
	}


	// somehow this is not working properly (macro expansion issue)
	std::pair<std::string, std::string> p1, p2;

	p1 = ke::splitStringToPair("One;Two;Three;Four;Five", ';', 0);
	p2 = std::pair<std::string, std::string>("One", "Two;Three;Four;Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two;Three;Four;Five", 0, ';'), std::pair<std::string, std::string>("One", "Two;Three;Four;Five"));

	p1 = ke::splitStringToPair("One;Two;Three;Four;Five", ';', 1);
	p2 = std::pair<std::string, std::string>("One;Two", "Three;Four;Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two;Three;Four;Five", 1, ';'), std::pair<std::string, std::string>("One;Two", "Three;Four;Five"));

	p1 = ke::splitStringToPair("One;Two;Three;Four;Five", ';', 2);
	p2 = std::pair<std::string, std::string>("One;Two;Three", "Four;Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two;Three;Four;Five", 2, ';'), std::pair<std::string, std::string>("One;Two;Three", "Four;Five"));

	p1 = ke::splitStringToPair("One;Two;Three;Four;Five", ';', 3);
	p2 = std::pair<std::string, std::string>("One;Two;Three;Four", "Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two;Three;Four;Five", 3, ';'), std::pair<std::string, std::string>("One;Two;Three;Four", "Five"));

	p1 = ke::splitStringToPair("One;Two;Three;Four;Five", ';', 4);
	p2 = std::pair<std::string, std::string>("One;Two;Three;Four;Five", "");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two;Three;Four;Five", 4, ';'), std::pair<std::string, std::string>("One;Two;Three;Four;Five", ""));
	

	p1 = ke::splitStringToPair("One;Two.Three;Four.Five", {";", "."}, 0);
	p2 = std::pair<std::string, std::string>("One", "Two.Three;Four.Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two.Three;Four.Five", 0, ";", "."), std::pair<std::string, std::string>("One", "Two.Three;Four.Five"));

	p1 = ke::splitStringToPair("One;Two.Three;Four.Five", {";", "."}, 1);
	p2 = std::pair<std::string, std::string>("One;Two", "Three;Four.Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two.Three;Four.Five", 1, ";", "."), std::pair<std::string, std::string>("One;Two", "Three;Four.Five"));

	p1 = ke::splitStringToPair("One;Two.Three;Four.Five", {";", "."}, 2);
	p2 = std::pair<std::string, std::string>("One;Two.Three", "Four.Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two.Three;Four.Five", 2, ";", "."), std::pair<std::string, std::string>("One;Two.Three", "Four.Five"));

	p1 = ke::splitStringToPair("One;Two.Three;Four.Five", {";", "."}, 3);
	p2 = std::pair<std::string, std::string>("One;Two.Three;Four", "Five");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two.Three;Four.Five", 3, ";", "."), std::pair<std::string, std::string>("One;Two.Three;Four", "Five"));

	p1 = ke::splitStringToPair("One;Two.Three;Four.Five", {";", "."}, 4);
	p2 = std::pair<std::string, std::string>("One;Two.Three;Four.Five", "");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("One;Two.Three;Four.Five", 4, ";", "."), std::pair<std::string, std::string>("One;Two.Three;Four.Five", ""));

	p1 = ke::splitStringToPair("Multichar; split; test", {"; "}, 0);
	p2 = std::pair<std::string, std::string>("Multichar", "split; test");
	ASSERT_EQUAL(p1, p2);
	// ASSERT_EQUAL(ke::splitStringToPair<std::pair>("Multichar, split, test", 0, ", "), std::pair<std::string, std::string>("Multichar", "split, test"));

	p1 = ke::splitStringToPair("Multichar; split; test", {"; "}, 1);
	p2 = std::pair<std::string, std::string>("Multichar; split", "test");
	ASSERT_EQUAL(p1, p2);
}



KE_TEST(splitString_transform)
{
	{
		std::string text = "|,.,.a.b.c,.d.,e.f,,g.h.i.j.k.l,m.n..o,p...q.r|s,.t|u.v.w.|,,x.y.z.";

		auto split1 = ke::splitString<std::string>(text, {".", ",", "|"}, [](const std::string& s) -> std::string { return s; });
		auto split2 = ke::splitString<char>(text, {".", ",", "|"}, [](const std::string& s) -> char { return (s.size() == 1) ? s[0] : ' '; });

		std::vector<std::string> correct1 = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
		std::vector<char> correct2 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		ASSERT_EQUAL(split1, correct1);
		ASSERT_EQUAL(split2, correct2);
	}

	{
		std::string text = ke::assembleString(std::views::iota(-100'000, 100'000) | std::views::transform([](const int x) -> std::string { return ke::toString(x); }), ", ");

		auto split = ke::splitString<int>(text, {", "}, [](const std::string& s) -> int {return ke::fromString<int>(s).value_or(-1); });
		ASSERT_EQUAL(split, std::views::iota(-100'000, 100'000) | std::ranges::to<std::vector>());
	}
}