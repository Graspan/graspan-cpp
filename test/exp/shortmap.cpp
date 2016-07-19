#include <iostream>
#include <random>
#include <ctime>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

std::vector<std::pair<char, char>> keysFound;
std::unordered_map<short, char> map;



short make_short(char a, char b) { return (short)(((short)a) << 8 | b); }

int main()
{
	srand(time(0));
	char chars[] = "abcdfgmxyz";
	char a, b;
	std::string str;

	int found = 0;

	for (int i = 1; i < 9; i++)
		map[make_short(chars[i], chars[i-1])] = (chars[i] + 1);

	for (int j = 0; j < 1000; j++)
	{
		a = rand() % 26 + 97;
		b = rand() % 26 + 97;

		if (map.find(make_short(a, b)) != map.end())
		{
			found++;
			keysFound.push_back({a, b});
		}
	}


	std::cout << "FOUND: " << found << std::endl;
	for (int i = 0; i < keysFound.size(); i++)
		std::cout << "(" << keysFound[i].first << "," << keysFound[i].second << ")  ";

	return 0;	
}
