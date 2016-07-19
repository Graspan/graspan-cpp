#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>

int main()
{
	std::vector<int> vec;

	for (int i = 0; i < 15; i++)
		vec.push_back(rand() % 50);

	std::sort(vec.begin(), vec.end());

	for (int j = 0; j < vec.size(); j++)
		std::cout << vec[j] << " ";
	std::cout << std::endl;

	for (int k = 0; k < 15; k++)
	{
		int num = rand() % 50;
		std::cout << "finding " << num << "... ";
		if (std::binary_search(vec.begin(), vec.end(), num))
			std::cout << "FOUND" << std::endl << std::endl;
		else
			std::cout << "NOT FOUND" << std::endl << std::endl;
	}

	return 0;
}
