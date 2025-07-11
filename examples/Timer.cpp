#include <KEUL/KEUL.hpp>

void foo(int x)
{
	std::println("{}", x);
}

int main()
{
	ke::Timer timer;

	int x = 0;
	bool condition = true;

	std::println("single call: ");
	timer.start(std::chrono::seconds(1), foo, x++);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::println("5 calls: ");
	timer.repeat(std::chrono::milliseconds(100), 5, foo, x++);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::println("while the condition is satisfied: ");
	timer.repeatWhile(std::chrono::milliseconds(100), &condition, foo, x++);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	condition = false;
	std::println("stop");
	std::this_thread::sleep_for(std::chrono::seconds(1));
}