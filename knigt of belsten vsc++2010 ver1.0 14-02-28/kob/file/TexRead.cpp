#include "TexRead.h"
#include "../log.h"

#include "../defines.h"

void getNextStringToComma(char* pCStr,char* pLine ,int * pos)
{
	//pLine[pos]���玟��','�܂���'\n'���̕������pCStr�ɃR�s�[
	//���̎�pos�̒l�̓R���}�����������̕������w���悤�ɍX�V����

	for(int i=0;i<STRING_LENGTH;i++)
	{
		pCStr[i]=pLine[*pos];
		(*pos)++;
		if(pCStr[i]=='\n')
		{
			pCStr[i]='\0';
			break;
		}
		if(pCStr[i]==',')//�R���}���������炻���܂ł𕶎���Ƃ���
		{
			pCStr[i]='\0';
			break;
		}

		if(pCStr[i]=='\0')
		{
			pCStr[i]='\0';
			break;
		}
	}
}

//-------------------------------------

TexRead::TexRead(const char *FilePath)
{
	//�R���X�g���N�^
	//FilePath�̃t�@�C����ǂݏo��
	//��Ƀe�L�X�g�t�@�C����csv��ǂݏo���N���X�ł�

	fout_log<<"TexRead �R���X�g���N�^ "<<FilePath<<endl;
	strcpy_s(m_filePath,FilePath);
	m_position=0;
	m_pFile=new File(FilePath);

	for(int i=0;i<STRING_LENGTH;i++)
	{
		m_Line[i]='\0';
	}

	m_bIsLoaded=false;

	if(m_pFile->hasReaded())
	{
		m_bIsLoaded=true;
	}
}

//-------------------------------------

TexRead::~TexRead()
{	
	SAFE_DELETE(m_pFile);
	fout_log<<"TexRead �f�X�g���N�^ "<<m_filePath<<endl;
}

//-----------------------

char* TexRead::readLine()
{
	//pLine�̍X�V
	//���݂�m_position���玟��'\n'�܂ł̕������pLine�ɃR�s�[����

	for(int i=0;i<STRING_LENGTH;i++)
	{
		if(m_position< (m_pFile->size()) )
		{
			m_Line[i]=m_pFile->operator()(m_position);
			m_position++;

			if(m_Line[i]=='\n')
			{
				if(i!=STRING_LENGTH-1)
				{
					m_Line[i+1]='\0';
				}
				break;
			}		
		}
		else break;
	}	
	return m_Line;
}


//-------------------------------------

bool TexRead::readLineSkipOverSolidus()
{
	//���̍s��ǂݏo���ithis->readLine ���Ăяo���j
	//���̉ߒ���'/'����n�܂�s��ǂݔ�΂��s�Ƃ��ǂݔ�΂�
	//�ǂݏo���̉ߒ��Ńt�@�C���̏I���܂Ō�������false��Ԃ��@����ȊO��true

	do
	{
		if(isEnd())
		{
			cout<<"��蔭��"<<endl;	
			return false;	
		}
		readLine();
	
	}while(*m_Line=='/');//   '/' ����n�܂�s�͓ǂݔ�΂�

return true;
}


//-------------------------------------

bool TexRead::isEnd()
{
	//m_position���w���Ă���ꏊ���t�@�C���̍Ō�Ȃ��true��Ԃ�

	if(m_position>=m_pFile->size())return true;
	else return false;
}

