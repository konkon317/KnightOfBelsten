#ifndef INCLUDE_LOG_H
#define INCLUDE_LOG_H

#include <iostream>
#include <fstream>
using namespace std;

#include "defines.h"

/*
class OutPutLog
{
	
	fstream* m_pStream;
	char m_fileName[FILE_PATH_LENGTH];
	
public :
	OutPutLog();
	~OutPutLog();

	void openLogFile(char* filename);	
	void closeLogFile(); 
	fstream& getStream(){return *m_pStream;}


};

extern OutPutLog g_Log;*/

extern ofstream fout_log;
//extern ofstream fout_sharedPtr_log;

extern bool sharedPtr_log_flag;
extern void StartLog_sharedPtr();
extern void EndLog_sharedPtr();

#endif




