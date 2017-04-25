#include "TexRead.h"
#include "../log.h"

#include "../defines.h"

void getNextStringToComma(char* pCStr,char* pLine ,int * pos)
{
	//pLine[pos]から次の','または'\n'迄の文字列をpCStrにコピー
	//その時posの値はコンマがあった次の文字を指すように更新する

	for(int i=0;i<STRING_LENGTH;i++)
	{
		pCStr[i]=pLine[*pos];
		(*pos)++;
		if(pCStr[i]=='\n')
		{
			pCStr[i]='\0';
			break;
		}
		if(pCStr[i]==',')//コンマがあったらそこまでを文字列とする
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
	//コンストラクタ
	//FilePathのファイルを読み出す
	//主にテキストファイルやcsvを読み出すクラスです

	fout_log<<"TexRead コンストラクタ "<<FilePath<<endl;
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
	fout_log<<"TexRead デストラクタ "<<m_filePath<<endl;
}

//-----------------------

char* TexRead::readLine()
{
	//pLineの更新
	//現在のm_positionから次の'\n'までの文字列をpLineにコピーする

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
	//次の行を読み出す（this->readLine を呼び出す）
	//その過程で'/'から始まる行を読み飛ばし行とし読み飛ばす
	//読み出しの過程でファイルの終わりまで言ったらfalseを返す　それ以外はtrue

	do
	{
		if(isEnd())
		{
			cout<<"問題発生"<<endl;	
			return false;	
		}
		readLine();
	
	}while(*m_Line=='/');//   '/' から始まる行は読み飛ばす

return true;
}


//-------------------------------------

bool TexRead::isEnd()
{
	//m_positionが指している場所がファイルの最後ならばtrueを返す

	if(m_position>=m_pFile->size())return true;
	else return false;
}

