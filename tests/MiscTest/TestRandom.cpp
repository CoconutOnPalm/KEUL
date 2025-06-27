#include <array>

#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>

// written on msvc compiler and I'm too lazy to check if it works on other compilers 

KE_TEST(Random)
{
	ke::Random generator(0);

#ifdef _MSC_VER
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


#elif defined(__GNUC__)

	std::array<int32_t, 10> correct_int32s = { 0, 13, 76, 46, 53, 22, 4, 68, 68, 94 };
	std::array<int64_t, 10> correct_int64s = { 412782219, 558719082, 893242245, 38121520, 58403993, 569761251, 721641163, 9265864, 412689419, 72771305 };
	std::array<uint64_t, 10> correct_uint64s = { 10769800460, 13440548094, 16868989162, 6404280277, 10800762626, 7249412912, 14294812216, 13066830086, 16521977050, 9257494317 };
	std::array<char, 10> correct_chars = { 's', 't', 'q', 'b', 'q', 'x', 'h', 'l', 't', 'm' };
	std::array<double, 10> correct_doubles = { 0.2749068400764783, 0.16650720019465282, 0.8976562867322144, 0.060564327533513665, 0.5045228949346109, 0.31903294108545305, 0.4939766852066831, 0.0907328945806298, 0.07374907522241696, 0.38414214796805357 };
	std::array<float, 10> correct_floats = { 0.2770818, 0.91381747, 0.52974737, 0.46444583, 0.94097996, 0.050083984, 0.76151425, 0.77020454, 0.8278173, 0.12536538 };
	std::array<std::string, 10> correct_strings = {
		"a\\et=QppHL", 
		"1V$Ogtp4-:", 
		"Gc7>^aE.pz", 
		".GVN{3\\^lM", 
		"4u.Gt0C-KK", 
		"x5vqPmL\\nc", 
		"z<QGsedc\"R", 
		"'Nawt.~JQJ", 
		"l4/Z!eH`on", 
		"(\\5Ez:;j;\""
	};
	std::array<std::string, 10> correct_strings2 = {
		"zvkEEGcqUT", 
		"QpiDNPsewO", 
		"InpLjlkcgR", 
		"SYylRpDINA", 
		"qXzvLAsLTS", 
		"tacxTaNofq", 
		"SHJIcUbeHm", 
		"ndvPIzAAmT", 
		"NdEpDYvGlX", 
		"tLrfoeLrvz"
	};

	std::array<bool, 100> chances = {
		true, true, true, false, false, true, true, false, true, false, 
		false, false, false, true, true, true, false, false, false, true, 
		true, true, false, true, false, true, true, false, true, false,
		true, false, false, true, false, false, true, true, true, false, 
		false, true, true, false, true, true, true, false, true, true, 
		true, false, false, true, true, true, false, true, false, true, 
		false, true, true, true, false, false, false, false, false, false, 
		true, false, false, true, false, true, true, true, true, true, 
		true, true, true, true, false, false, false, false, true, false, 
		true, true, true, true, true, false, true, true, true, false
	};

#endif


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

	for (size_t i = 0; i < 10000; i++)
	{
		ASSERT_TRUE(ke::InRange(ke::ClosedRange<uint32_t>(0, 10), generator.Value<uint32_t>(ke::ClosedRange<uint32_t>(0u, 10u))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange<uint32_t>(1, 9),  generator.Value<uint32_t>(ke::OpenRange<uint32_t>(0u, 10u))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange<uint32_t>(0, 9),  generator.Value<uint32_t>(ke::HalfOpenRange<uint32_t>(0u, 10u))));

		ASSERT_TRUE(ke::InRange(ke::ClosedRange(0, 10), generator.Int32(ke::ClosedRange(0, 10))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange(1, 9),  generator.Int32(ke::OpenRange(0, 10))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange(0, 9),  generator.Int32(ke::HalfOpenRange(0, 10))));

		ASSERT_TRUE(ke::InRange(ke::ClosedRange('a', 'e'), generator.Char(ke::ClosedRange('a', 'e'))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange('b', 'd'), generator.Char(ke::OpenRange('a', 'e'))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange('a', 'd'), generator.Char(ke::HalfOpenRange('a', 'e'))));

		constexpr double eps = std::numeric_limits<double>::epsilon();

		ASSERT_TRUE(ke::InRange(ke::ClosedRange(0.0, 0.5), generator.Double(ke::ClosedRange(0.0, 0.5))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange(0.0 + eps, 0.5 - eps), generator.Double(ke::OpenRange(0.0, 0.5))));
		ASSERT_TRUE(ke::InRange(ke::ClosedRange(0.0, 0.5 - eps), generator.Double(ke::HalfOpenRange(0.0, 0.5))));
	}
}