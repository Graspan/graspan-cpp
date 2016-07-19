#include <iostream>
#include <vector>
#include <random>

int main()
{
	for (int i = 0; i < 15; i++)
	{
		int size = rand() % 1000;
		std::cout << "SIZE: " << size << std::endl;

		std::vector<int> vec;
		vec.reserve(size);

		std::cout << "CAP: " << vec.capacity() << std::endl;
	}

	return 0;
}
