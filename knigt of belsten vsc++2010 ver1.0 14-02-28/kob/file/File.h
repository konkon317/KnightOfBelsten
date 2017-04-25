#ifndef INCLUDE_FILE_H
#define INCLUDE_FILE_H

#include "../defines.h"

#include <iostream>
using namespace std;

class File{
	private :
	
		char mFilePath[FILE_PATH_LENGTH];
		char* mData;
		int mSize;

	public :
		File(const char* filename);
		~File();
		const int size()const;
		const char* data()const ;

		const char& operator()(int position)const;
		char& operator()(int position);

		bool hasReaded(){if(mData)return true;else return false;}
		

		unsigned getUnsigned(int position)const;
};


#endif 