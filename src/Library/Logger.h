#ifndef LOGGER_H
#define LOGGER_H

#include "../utilities/globalDefinitions.hpp"
#include <fstream>
#include <ctime>

using namespace std;

class Logger{
private:
	std::ofstream fout;
	time_t cur_time;
	struct tm *cur_tm;

	char buf[1024];
	inline void Date(struct tm *cur_tm){sprintf(buf,"%d.%02d.%02d %02d:%02d:%02d\n",cur_tm->tm_year + 1900, cur_tm->tm_mon, cur_tm->tm_mday, cur_tm->tm_hour, cur_tm->tm_min, cur_tm->tm_sec);}
public:
	Logger();
	Logger(string logFile);
	~Logger();

	void info(string str);
	void warning(string str);
	void severe(Error err);
};

#endif
