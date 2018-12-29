#include "StaticArray.hpp"
#include "Timer.hpp"

int main()
{
	StaticArray<10, int> x = StaticArray<10, int>(3);
	int counter = 0;
	for (auto& i : x)
		i = counter++;

	StaticArray<15, int> y(x);
	y[12] = 2254;
	y[2] = 331;

	x = StaticArray<10, int>(y);

	auto z = StaticArray<10, int, int>(x);
	z[-1] = 4;
	z[-0] = 0;

	auto res = Timer<double, std::milli, std::chrono::steady_clock>::measureExecution(&StaticArray<10, int, int>::reverse, z);
	printf("time: %f", res.count());

	auto zx = z.reverseCopy();
	return 0;
}