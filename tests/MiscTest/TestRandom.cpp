#include <array>

#include <Utility.h>
#include <Testing.h>

// written on msvc compiler and I'm too lazy to check if it works on other compilers 
#ifdef _MSC_VER

KE_TEST(Random)
{
	ke::Random generator(0);

	std::array<int32_t, 10> correct_int32s = { 55, 59, 72, 85, 60, 86, 55, 85, 42, 62 };
	std::array<int64_t, 10> correct_int64s = { 646248221, 384997326, 438149623, 298237070, 891881229, 57656262, 963699102, 273383638, 384058080, 791933309 };
	std::array<uint64_t, 10> correct_uint64s = { 14746024719, 10759726058, 9713417520, 15032945226, 9048753940, 12778062519, 9418898451, 16485861854, 6684209331, 15441047016 };
	std::array<char, 10> correct_chars = { 'm', 'u', 'u', 'l', 'n', 'u', 'r', 'd', 's', 'q' };
	std::array<double, 10> correct_doubles = { 0.1433532856362918, 0.944668918740324, 0.5218483283553774, 0.41466194114319693, 0.26455561152510354, 0.7742336865482694, 0.45615033612980466, 0.5684339483772755, 0.018789798052799463, 0.6176355009256259 };
	std::array<float, 10> correct_floats = { 0.14967486f, 0.6120957f, 0.22232139f, 0.616934f, 0.38648897f, 0.94374806f, 0.9025985f, 0.6818203f, 0.44994998f, 0.3595079f };
	std::array<std::string, 10> correct_strings = {
		"Jb&_`4->CV",
		"J}*40^8L7/",
		"+^-3Cn*o*|",
		"M|Yf$;,<,>",
		"G\'bV9R)Wx>",
		"_-d<2X\"n!`",
		":f{8WXV5zK",
		"pb<mFsWsbe",
		"Pz]HZ\"=_<[",
		"I-=VXV^^Iu"
	};

	std::array<std::string, 10> correct_strings2 = {
		"jlXuScxszD",
		"WeQdWUokbS",
		"lswzwaJSEn",
		"bfaufIYSAE",
		"QpGYpNPSIK",
		"feyTmFGbli",
		"SJEABRlNXZ",
		"frGatIJPvQ",
		"whuEYrfYtG",
		"fNaFlJMhpW"
	};

	std::array<bool, 100> chances = {
		false, true, false, false, true, true, true, false, false, true,
		true, false, false, true, true, true, true, true, true, true,
		false, false, true, false, false, false, true, false, true, true,
		false, false, false, false, true, false, true, true, true, true,
		false, true, true, true, false, false, true, false, false, false,
		false, true, false, false, true, true, false, true, false, false,
		false, false, false, true, true, false, true, true, false, false,
		true, false, false, false, true, false, false, false, true, true,
		false, false, true, false, false, true, false, true, false, true,
		false, false, false, true, false, true, true, false, true, true
	};


	for (auto& expect : correct_int32s)
		ASSERT_EQUAL(expect, generator.Int32(0, 100));

	for (auto& expect : correct_int64s)
		ASSERT_EQUAL(expect, generator.Int64(1'000'000, 1'000'000'000));
	 
	for (auto& expect : correct_uint64s)
		ASSERT_EQUAL(expect, generator.UInt64(5'000'000'000, 17'000'000'000));

	for (auto& expect : correct_chars)
		ASSERT_EQUAL(expect, generator.Char('a', 'z'));

	for (auto& expect : correct_doubles)
		ASSERT_EQUAL(expect, generator.Double(0.0, 1.0));

	for (auto& expect : correct_floats)
		ASSERT_EQUAL(expect, generator.Float(0.0f, 1.0f));

	for (auto& expect : correct_strings)
		ASSERT_EQUAL(expect, generator.String(10));

	for (auto& expect : correct_strings2)
		ASSERT_EQUAL(expect, generator.String(10, ke::ClosedRange('a', 'z'), ke::ClosedRange('A', 'Z')));

	for (size_t i = 0; i < chances.size(); i++)
		ASSERT_EQUAL(chances[i], generator.Chance(0.5));
}

#endif