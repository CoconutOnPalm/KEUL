#include <set>
#include <unordered_set>
#include <list>
#include <vector>

#include <KEUL/KEUL.hpp>


struct BenchmarkTest
{
	double insert;
	double find;
	double remove;
};

constexpr size_t test_repetitions = 50;
constexpr size_t test_size = 1'000;


BenchmarkTest test_set();
BenchmarkTest test_unordered_set();
BenchmarkTest test_list();
BenchmarkTest test_vector();


void print_results(const std::string_view name, const BenchmarkTest& results)
{
	// using ke formatting:
	// title				will be bold (more intense color)
	// --					will be dimmer
	// insert/find/remove	will be default
	// results				will be underlined

	ke::println("[b]{}", name);
	ke::println("[f]--[0]insert: [u]{:.3f}", results.insert);
	ke::println("[f]--[0]find:   [u]{:.3f}", results.find);
	ke::println("[f]--[0]remove: [u]{:.3f}", results.remove);
}


int main()
{
	// test avarage times of operations: { insert, find, delete } 
	// between 4 different stl data structures: (std::) { set, unordered_set, list, vector }
	ke::println("[b;c]RESULTS:");
	print_results("std::set", test_set());
	print_results("std::unordered_set", test_unordered_set());
	print_results("std::list", test_list());
	print_results("std::vector", test_vector());
}


BenchmarkTest test_set()
{
	ke::LoopBenchmark insert;
	ke::LoopBenchmark find;
	ke::LoopBenchmark remove;

	std::set<int> set;

	auto raw_data = std::views::iota(0ull, test_size);
	std::vector<int> data(raw_data.begin(), raw_data.end());
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ranges::shuffle(data, gen);

	// insert
	for (size_t k = 0; k < test_repetitions; k++)
	{
		insert.startIteration();
		for (const auto el : data)
			set.insert(el);
		insert.endIteration();

		find.startIteration();
		for (const auto el : data)
			set.find(el);
		find.endIteration();

		remove.startIteration();
		for (const auto el : data)
			set.erase(el);
		remove.endIteration();
	}

	return BenchmarkTest{
		.insert = static_cast<double>(insert.stop()) / static_cast<double>(test_repetitions),
		.find = static_cast<double>(find.stop()) / static_cast<double>(test_repetitions),
		.remove = static_cast<double>(remove.stop()) / static_cast<double>(test_repetitions),
	};
}

BenchmarkTest test_unordered_set()
{
	ke::LoopBenchmark insert;
	ke::LoopBenchmark find;
	ke::LoopBenchmark remove;

	std::unordered_set<int> unordered_set;

	auto raw_data = std::views::iota(0ull, test_size);
	std::vector<int> data(raw_data.begin(), raw_data.end());
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ranges::shuffle(data, gen);

	// insert
	for (size_t k = 0; k < test_repetitions; k++)
	{
		insert.startIteration();
		for (const auto el : data)
			unordered_set.insert(el);
		insert.endIteration();

		find.startIteration();
		for (const auto el : data)
			unordered_set.find(el);
		find.endIteration();

		remove.startIteration();
		for (const auto el : data)
			unordered_set.erase(el);
		remove.endIteration();
	}

	return BenchmarkTest{
		.insert = static_cast<double>(insert.stop()) / static_cast<double>(test_repetitions),
		.find = static_cast<double>(find.stop()) / static_cast<double>(test_repetitions),
		.remove = static_cast<double>(remove.stop()) / static_cast<double>(test_repetitions),
	};
}

BenchmarkTest test_list()
{
	ke::LoopBenchmark insert;
	ke::LoopBenchmark find;
	ke::LoopBenchmark remove;

	std::list<int> list;

	auto raw_data = std::views::iota(0ull, test_size);
	std::vector<int> data(raw_data.begin(), raw_data.end());
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ranges::shuffle(data, gen);

	// insert
	for (size_t k = 0; k < test_repetitions; k++)
	{
		insert.startIteration();
		for (const auto el : data)
			list.push_back(el);
		insert.endIteration();

		find.startIteration();
		for (const auto el : data)
			std::ranges::find(data, el);
		find.endIteration();

		remove.startIteration();
		for (const auto el : data)
			list.remove(el);
		remove.endIteration();
	}

	return BenchmarkTest{
		.insert = static_cast<double>(insert.stop()) / static_cast<double>(test_repetitions),
		.find = static_cast<double>(find.stop()) / static_cast<double>(test_repetitions),
		.remove = static_cast<double>(remove.stop()) / static_cast<double>(test_repetitions),
	};
}

BenchmarkTest test_vector()
{
	ke::LoopBenchmark insert;
	ke::LoopBenchmark find;
	ke::LoopBenchmark remove;

	std::vector<int> vector;

	auto raw_data = std::views::iota(0ull, test_size);
	std::vector<int> data(raw_data.begin(), raw_data.end());
	std::random_device rd;
	std::mt19937 gen(rd());

	std::ranges::shuffle(data, gen);

	// insert
	for (size_t k = 0; k < test_repetitions; k++)
	{
		insert.startIteration();
		for (const auto el : data)
			vector.push_back(el);
		insert.endIteration();

		find.startIteration();
		for (const auto el : data)
			std::ranges::find(data, el);
		find.endIteration();

		remove.startIteration();
		for (const auto el : data)
			std::ranges::remove(data, el);
		remove.endIteration();
	}

	return BenchmarkTest{
		.insert = static_cast<double>(insert.stop()) / static_cast<double>(test_repetitions),
		.find = static_cast<double>(find.stop()) / static_cast<double>(test_repetitions),
		.remove = static_cast<double>(remove.stop()) / static_cast<double>(test_repetitions),
	};
}