#include "Loader.h"


void Loader::loadBinary(char * fileName)
{
	static char s[32 + 1] = { '0', };
	FILE *fp;
	char n2[4], label;
	int src, degree, dst;
	

	fp = fopen(fileName, "rb");

	while (NULL != fread(&src, 4, 1, fp)) {
		fread(&degree, 4, 1, fp);
		std::cout << src << " " << degree << " ";

		for (int i = 0; i < degree; i++) {
			fread(&dst, 4, 1, fp);

			fread(&label, 1, 1, fp);

			std::cout << dst << " " << (int)label << " ";
		}
		std::cout << std::endl;

	}
}
