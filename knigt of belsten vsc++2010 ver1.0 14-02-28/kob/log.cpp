#include "log.h"

/*
OutPutLog::OutPutLog()
{
	m_pStream=NULL;
	cout<<"���O�@�R���X�g���N�^"<<endl;

}

OutPutLog::~OutPutLog()
{
	closeLogFile();
	cout<<"���O�@�f�X�g���N�^"<<endl;

}

void OutPutLog::openLogFile(char* filename)
{
	m_pStream=new fstream(filename);
	strcpy_s(m_fileName,filename);
	if(!m_pStream)
	{
		cout <<"�t�@�C�����I�[�v���ł��܂���ł���"<<endl;
		SAFE_DELETE(m_pStream);
	}
}

void OutPutLog::closeLogFile()
{
	if(m_pStream->operator !())
	{
		m_pStream->close();
		SAFE_DELETE(m_pStream);
	}

}
*/
bool sharedPtr_log_flag=false;

ofstream fout_log("gameLog.txt");
//ofstream fout_sharedPtr_log("sharedPtr_log.txt");


void StartLog_sharedPtr()
{
	sharedPtr_log_flag=true;
}
void EndLog_sharedPtr()
{
	sharedPtr_log_flag=false;
}


