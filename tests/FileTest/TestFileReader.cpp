#include <filesystem>

#include <KEUL/KEUL.hpp>
#include <KEUL/UnitTests.hpp>



/*
test file contents:

Basic.txt: (UTF-8 + BOM encoding)

C:\Users\TestUser\Documents\project\file1.txt
C:\Program Files\MyApp\data\config.json
D:\Backup\Old Versions\backup_2023-08-04.zip
E:\Music\Albums\Best of 80's\track01.mp3
C:\Users\TestUser\Desktop\My Projects\Project_#42\main.cpp
F:\Photos\Vacation\2024\summer_trip!.jpg
G:\Work\Reports\Q1 2024\financial report.xlsx
C:\Users\TestUser\Downloads\New Folder (2)\document (final).docx
H:\Movies\Comedy\Funny Movie @ Home.mkv

// a comment

I:\Games\Installed\Game123\levels\level-2~final.dat
J:\Documents\Personal\Śmieszne koty\silly boy koty.txt


Unicode.txt: (UTF-8 + BOM encoding)

!@#$%^&*()_+-=[]{}|;':",./<>?`~
¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿
ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß
àáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ
ĀāĂăĄąĆćĈĉĊċČčĎďĐđĒēĔĕĖėĘęĚěĜĝĞğ
ĠġĢģĤĥĦħĨĩĪīĬĭĮįİıĲĳĴĵĶķĸĹĺĻļĽ
ľĿŀŁłŃńŅņŇňŉŊŋŌōŎŏŐőŒœŔŕŖŗŘř
ŚśŜŝŞşŠšŢţŤťŦŧŨũŪūŬŭŮůŰűŲųŴŵ
ŶŷŸŹźŻżŽžſ
ǍǎǏǐǑǒǓǔǕǖǗǘǙǚǛǜǝǞǟǠǡǢǣǤǥǦǧǨ
ǩǪǫǬǭǮǯǰǱǲǳǴǵǶǷǸǹǺǻǼǽǾǿȀȁ
ȂȃȄȅȆȇȈȉȊȋȌȍȎȏȐȑȒȓȔȕȖȗȘșȚțȜȝȞȟ
ȠȡȢȣȤȥȦȧȨȩȪȫȬȭȮȯȰȱȲȳȴȵȶȷȸȹȺ
ȻȼȽȾȿɀɁɂɃɄɅɆɇɈɉɊɋɌɍɎɏɐɑɒɓɔɕɖɗɘ
əɚɛɜɝɞɟɠɡɢɣɤɥɦɧɨɩɪɫɬɭɮɯɰɱɲɳɴɵɶɷɸ
ɹɺɻɼɽɾɿʀʁʂʃʄʅʆʇʈʉʊʋʌʍʎʏʐʑʒʓʔʕʖʗʘʙʚʛʜʝʞʟʠʡʢʣʤʥʦʧʨʩʪʫʬʭʮʯʰʱ
ʲʳʴʵʶʷʸʹʺʻʼʽʾʿˀˁ˂˃˄˅ˆˇˈˉˊˋˌˍˎˏːˑ˒˓˔˕˖˗˘˙˚˛˜˝˞˟ˠˡˢˣˤ˥˦˧˨˩˪˫ˬ˭ˮ˯
˰˱˲˳˴˵˶˷˸˹˺˻˼˽˾˿


LoremIpsum.txt: (Default by Visual Studio)

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum

*/

#ifdef PROJECT_SOURCE_DIR
const std::string source_dir = PROJECT_SOURCE_DIR;
#else
const std::string source_dir = "";
#endif


KE_TEST(FileReader)
{
	// somehow on win11 '/' is needed before the path
	const std::string basic_txt_path = source_dir + "tests/assets/Basic.txt";
	const std::string unicode_txt_path = source_dir + "tests/assets/Unicode.txt";
	const std::string lorem_ipsum_txt_path = source_dir + "tests/assets/LoremIpsum.txt";

	if (!std::filesystem::exists(basic_txt_path))
	{
		ke::_internal::EngineLog::Warning("Basic.txt does not exist. Skipping FileReader tests.");
		ke::_internal::EngineLog::Info("Current directory: {}. Searching for: {}", std::filesystem::current_path().string(), basic_txt_path);
		return;
	}

	ke::FileReader reader;

	// temporary disable logging
	ke::SimpleLogger::setLayer(ke::LogLayer::Off);

	ASSERT_FALSE(reader.open("noexisting.txt"));
	ASSERT_FALSE(reader.isOpen());

	ASSERT_FALSE(reader.open("./"));
	ASSERT_FALSE(reader.isOpen());

	ke::SimpleLogger::setLayer(ke::LogLayer::Debug);

	ASSERT_TRUE(reader.open(basic_txt_path));
	ASSERT_TRUE(reader.isOpen());


	auto data = reader.readAll();

	ASSERT_EQUAL(data.size(), 11);

	std::vector<std::string> correct_data = {
		"C:\\Users\\TestUser\\Documents\\project\\file1.txt",
		"C:\\Program Files\\MyApp\\data\\config.json",
		"D:\\Backup\\Old Versions\\backup_2023-08-04.zip",
		"E:\\Music\\Albums\\Best of 80's\\track01.mp3",
		"C:\\Users\\TestUser\\Desktop\\My Projects\\Project_#42\\main.cpp",
		"F:\\Photos\\Vacation\\2024\\summer_trip!.jpg",
		"G:\\Work\\Reports\\Q1 2024\\financial report.xlsx",
		"C:\\Users\\TestUser\\Downloads\\New Folder (2)\\document (final).docx",
		"H:\\Movies\\Comedy\\Funny Movie @ Home.mkv",
		"I:\\Games\\Installed\\Game123\\levels\\level-2~final.dat",
		"J:\\Documents\\Personal\\Śmieszne koty\\silly boy koty.txt",
	};

	for (size_t i = 0; i < data.size(); ++i)
	{
		ASSERT_EQUAL(data[i], correct_data[i]);
	}

	reader.close();

	if (!reader.open(unicode_txt_path))
	{
		ke::_internal::EngineLog::Warning("Unicode.txt does not exist. Skipping FileReader tests.");
		ke::_internal::EngineLog::Info("Current directory: {}", std::filesystem::current_path().string());
		return;
	}

	data = reader.readAll();

	ASSERT_EQUAL(data.size(), 18);

	correct_data = {
		"!@#$%^&*()_+-=[]{}|;':\",./<>?`~",
		"¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿",
		"ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß",
		"àáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ",
		"ĀāĂăĄąĆćĈĉĊċČčĎďĐđĒēĔĕĖėĘęĚěĜĝĞğ",
		"ĠġĢģĤĥĦħĨĩĪīĬĭĮįİıĲĳĴĵĶķĸĹĺĻļĽ",
		"ľĿŀŁłŃńŅņŇňŉŊŋŌōŎŏŐőŒœŔŕŖŗŘř",
		"ŚśŜŝŞşŠšŢţŤťŦŧŨũŪūŬŭŮůŰűŲųŴŵ",
		"ŶŷŸŹźŻżŽžſ",
		"ǍǎǏǐǑǒǓǔǕǖǗǘǙǚǛǜǝǞǟǠǡǢǣǤǥǦǧǨ",
		"ǩǪǫǬǭǮǯǰǱǲǳǴǵǶǷǸǹǺǻǼǽǾǿȀȁ",
		"ȂȃȄȅȆȇȈȉȊȋȌȍȎȏȐȑȒȓȔȕȖȗȘșȚțȜȝȞȟ",
		"ȠȡȢȣȤȥȦȧȨȩȪȫȬȭȮȯȰȱȲȳȴȵȶȷȸȹȺ",
		"ȻȼȽȾȿɀɁɂɃɄɅɆɇɈɉɊɋɌɍɎɏɐɑɒɓɔɕɖɗɘ",
		"əɚɛɜɝɞɟɠɡɢɣɤɥɦɧɨɩɪɫɬɭɮɯɰɱɲɳɴɵɶɷɸ",
		"ɹɺɻɼɽɾɿʀʁʂʃʄʅʆʇʈʉʊʋʌʍʎʏʐʑʒʓʔʕʖʗʘʙʚʛʜʝʞʟʠʡʢʣʤʥʦʧʨʩʪʫʬʭʮʯʰʱ",
		"ʲʳʴʵʶʷʸʹʺʻʼʽʾʿˀˁ˂˃˄˅ˆˇˈˉˊˋˌˍˎˏːˑ˒˓˔˕˖˗˘˙˚˛˜˝˞˟ˠˡˢˣˤ˥˦˧˨˩˪˫ˬ˭ˮ˯",
		"˰˱˲˳˴˵˶˷˸˹˺˻˼˽˾˿",
	};

	for (size_t i = 0; i < data.size(); ++i)
	{
		ASSERT_EQUAL(data[i], correct_data[i]);
	}


	reader.close();

	// check if no-BOM works

	if (!reader.open(lorem_ipsum_txt_path))
	{
		ke::_internal::EngineLog::Warning("LoremIpsum.txt does not exist. Skipping FileReader tests.");
		ke::_internal::EngineLog::Info("Current directory: {}", std::filesystem::current_path().string());
		return;
	}
	
	data = reader.readAll();

	ASSERT_EQUAL(data.size(), 1);
	ASSERT_EQUAL(data[0], "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum");

}