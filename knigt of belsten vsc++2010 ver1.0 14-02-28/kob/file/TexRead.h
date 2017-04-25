#ifndef INCLUDE_TEX_READ
#define INCLUDE_TEX_READ


#include "File.h"

extern void getNextStringToComma(char* pCStr,char* pLine ,int * pos);

class TexRead
{
	//主にテキストファイルやcsvを読み出すクラスです
private:

	char m_filePath[FILE_PATH_LENGTH];
	char m_Line[STRING_LENGTH];
	int m_position;
	File* m_pFile;
	bool m_bIsLoaded;

public :
	TexRead(const char* FilePath);
	~TexRead();

	char* readLine();
	char* getLine(){return m_Line;}
	bool readLineSkipOverSolidus();

	void setFirst(){m_position=0;}

	bool isEnd();
	bool isLoaded(){return m_bIsLoaded;}
};


#endif