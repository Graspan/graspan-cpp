#ifndef LOGGER_H
#define LOGGER_H

#include "../utilities/globalDefinitions.hpp"
#include <fstream>
#include <ctime>


class Logger{
private:
	std::ofstream fout;
	time_t cur_time;
	struct tm *cur_tm;
	//will reduce function
	//it will fix to return string type
	inline void Date(struct tm *cur_tm){cout << cur_tm->tm_year + 1900 << "." <<cur_tm->tm_mon << "." << cur_tm->tm_mday << "  " << cur_tm->tm_hour << ":" << cur_tm->tm_min << ":" << cur_tm->tm_sec << endl;}
	inline void fDate(struct tm *cur_tm){fout << cur_tm->tm_year + 1900 << "." <<cur_tm->tm_mon << "." << cur_tm->tm_mday << "  " << cur_tm->tm_hour << ":" << cur_tm->tm_min << ":" << cur_tm->tm_sec << endl;}
	//inline string Date(struct tm *cur_tm){return (cur_tm->tm_year + 1900) + "." + (cur_tm->tm_mon) + "." + (cur_tm->tm_mday) + " " + (cur_tm->tm_hour) ":" + (cur_tm->tm_min) + ":" + (cur_tm->tm_sec) + (" : ");}
public:
	Logger();
	Logger(string logFile);
	~Logger();

	void info(string str);
	void warning(string str);
	void severe(Error err);
};

#endif
