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
	cout<< buf << "INFO: " <<str<<endl;
	fout<< buf << "INFO: "<<str<<endl;
}

void Logger::warning(string str){
	cur_time = time(NULL);
	cur_tm = localtime(&cur_time);
	Date(cur_tm);
	cout<< buf << "WARNING: " <<str<<endl;
	fout<< buf << "WARNING: "<<str<<endl;
}

//if you want to add other error, you should add the case
void Logger::severe(Error err){
	cur_time = time(NULL);
	cur_tm = localtime(&cur_time);
	Date(cur_tm);
	cout<< buf;
	fout<< buf;

	switch(err){
	case FOPEN:
		cout << "can't make file" << endl;
		fout << "can't make file" << endl;
		break;
	case FCLOSE:
		cout << "can't close file" << endl;
		fout << "can't close file" << endl;
		break;
	default: break;
	}
}
