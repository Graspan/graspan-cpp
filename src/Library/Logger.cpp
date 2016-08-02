#include "Logger.h"

Logger::Logger(){
	try{
		fout.open("logFile");
		if(!fout) throw 0;
	} catch(int exception){
		severe(exception);
		return;
	}	 
}

Logger::Logger(string logFile){
	try{
		fout.open(logFile);
		if(!fout) throw 0;
	} catch(int exception){
		severe(exception);
		return;
	}	 
}

Logger::~Logger(){
	try{
		fout.close();
		if(!fout) throw 1;
	} catch(int exception){
		severe(exception);
		return;
	}
}

void Logger::info(string str){
	cur_time = time(NULL);
	//for local time
	cur_tm = localtime(&cur_time);
	Date(cur_tm);
	cout<< "INFO: " <<str<<endl;
	//fDate(cur_tm);
	//fout<<"INFO: "<<str<<endl;
}

void Logger::warning(string str){
	cur_time = time(NULL);
	//for local time
	cur_tm = localtime(&cur_time);
	Date(cur_tm);
	cout<< "WARNING: " <<str<<endl;
	//fDate(cur_tm);
	//fout<<"WARNING: "<<str<<endl;
}

//if you want to add other error, you should add the case
void Logger::severe(int exception){
	switch(exception){
	case 0:
		cout << "can't make file" << endl;
		break;
	case 1:
		cout << "can't close file" << endl;
		break;
	default: break;
	}
}
