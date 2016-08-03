#include "Logger.h"

Logger::Logger(){
	try{
		fout.open("../resource/logFile");
		if(!fout) throw FOPEN;
	} catch(Error err){
		severe(err);
		return;
	}	 
}

Logger::Logger(string logFile){
	try{
		fout.open(logFile);
		if(!fout) throw FOPEN;
	} catch(Error err){
		severe(err);
		return;
	}	 
}

Logger::~Logger(){
	try{
		fout.close();
		if(!fout) throw FCLOSE;
	} catch(Error err){
		severe(err);
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
void Logger::severe(Error err){
	switch(err){
	case FOPEN:
		cout << "can't make file" << endl;
		break;
	case FCLOSE:
		cout << "can't close file" << endl;
		break;
	default: break;
	}
}
