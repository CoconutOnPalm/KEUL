#include <KEUL/KEUL.hpp>

struct Point
{
	float x, y;
};

Point transform(const std::string& point_raw)
{
	std::string bracketless = ke::trimString(point_raw, { '(', ')' }); // strip the point of any brackets:  "(x,y)" -> "x,y"
	auto pair = ke::splitStringToPair(bracketless, ',', 0); // split into pair: 
	return Point { 
		.x = ke::tryFromString<float>(pair.first, 0), 
		.y = ke::tryFromString<float>(pair.second, 0) 
	};
}

int main()
{
	// decode received data info vector of points
	std::string_view points_raw =
		"(-0.732,0.415);(0.123,-0.987);(0.876,0.543);(-0.321,-0.654);(0.001,0.999);"
		"(-0.555,0.222);(0.789,-0.333);(-0.101,0.101);(0.456,-0.789);(0.000,0.000);";

	std::vector<Point> points_decoded = ke::splitString<Point>(points_raw, ';', transform);

	for (const auto& point : points_decoded)
		std::println("({}, {})", point.x, point.y);
}
