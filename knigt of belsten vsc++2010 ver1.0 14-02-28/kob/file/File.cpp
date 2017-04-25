#include "File.h"

#include <iostream>
#include <fstream>
using namespace std;
#include "../log.h"


File::File(const char* filename):mSize(0),mData(0)
{
	//�t�@�C����ǂݍ���Ń��������T�C�Y���m�ی�R�s�[
	//���̌�t�@�C���N���[�Y

	strcpy_s(mFilePath,filename);
	fout_log<< "file �R���X�g���N�^ "<<mFilePath<<" ";
	fout_log <<"read ";
	mData=NULL;

	ifstream in(filename,ifstream::binary);
	
	if (in)
	{
		fout_log <<"true ";

		in.seekg(0,ifstream::end);
		mSize=static_cast<int>(in.tellg());
		in.seekg(0,ifstream::beg);
		mData=new char [mSize];
		in.read(mData,mSize);
		in.close();
	}
	else 
	{
		fout_log <<"false ";
	}
	fout_log<<endl;
}

//----------------------------------------------------------------
File::~File()
{
	fout_log<<"file �f�X�g���N�^ "<<mFilePath<<endl;
	SAFE_DELETE_ARRAY(mData);//���
}
//----------------------------------------------------------------
const char* File::data()const
{
	return mData;
}

//----------------------------------------------------------------
const char& File::operator()(int position)const 
{
	return mData[position];
}

//----------------------------------------------------------------
char& File::operator()(int position)
{
	return mData[position];
}

//----------------------------------------------------------------
const int File::size()const
{
	return mSize;
}

//----------------------------------------------------------------

unsigned File::getUnsigned(int position)const
{
	unsigned r=0;
	if (position>=0&&position<mSize-4)
	{	
		const unsigned char * up;
		up=reinterpret_cast<const unsigned char*>(mData);
		r|=up[position];
		r|=up[position+1]<<8*1;
		r|=up[position+2]<<8*2;
		r|=up[position+3]<<8*3;
	}
	return r;
}


//----------------------------------------------------------------