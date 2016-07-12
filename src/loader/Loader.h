#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <set>



class Loader {
private:
	char *part;
	char *bpart;
	std::vector<std::pair<int, std::string>> *data;

public:
	void loadBinary(char *fileName);
};


#endif