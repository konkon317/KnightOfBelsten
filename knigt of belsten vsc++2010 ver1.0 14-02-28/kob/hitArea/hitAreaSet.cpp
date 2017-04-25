#include "hitAreaSet.h"
#include "../log.h"

HitAreaSet::HitAreaSet()
{
	fout_log<<"hitAreaSet コンストラクタ"<<endl;
	m_pHitArea_Array=NULL;
	//m_pFilePathToRead_Array=NULL;
	m_max=0;
	strcpy_s(m_filePath,"nodata");	
	m_isInitialized=false;

}


HitAreaSet::~HitAreaSet()
{
	SAFE_DELETE_ARRAY(m_pHitArea_Array);
	//SAFE_DELETE_ARRAY(m_pFilePath_Array);
	fout_log<<"hitAreaSet デストラクタ "<<m_filePath<<endl;
}

void HitAreaSet::reset()
{
	SAFE_DELETE_ARRAY(m_pHitArea_Array);
	m_max=0;
	strcpy_s(m_filePath,"nodata");	
	
}


void HitAreaSet::initialize(const char *filePath)
{
	fout_log<<"hitAreaSet initialize "<<filePath<<endl;
	strcpy_s(m_filePath,filePath);	

	TexRead texRead(m_filePath);

	if(!(texRead.isLoaded()))
	{
		return;
	}
	
	texRead.setFirst();
	
	
	string str;

	char inputC[STRING_LENGTH];
	char* pLine;

	int pos=0;//今読んでいる位置
	pLine=texRead.readLine();
	
	getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

	str=inputC;

	if(str!="<pMax>")//内容に間違いがある場合
	{	
		return;	
	}

	
	//コマの数を読みだす
	getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

	m_max=atoi(inputC);	//コマの数を格納

	if(m_max>0&&m_pHitArea_Array==NULL)
	{
		m_pHitArea_Array=new HitArea[m_max];	
	}

	string filepath="noData";

	for(int i=0;i<m_max;i++)
	{
		//texReadのLineを更新　読み出しの過程でファイルが終了していないかのチェック
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"問題発生"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
	
		getNextStringToComma(inputC,pLine,&pos);//次の文字列をinputCにコピーする　pLine[pos]から','または'\n'まで　

		filepath=inputC;

		if(filepath!="nodata")
		{
			m_pHitArea_Array[i].initialize(filepath.c_str());
		}
	}

	m_isInitialized=true;

}

void HitAreaSet::show()
{
	fout_log<<"hitAreaSet show";
	fout_log<<m_filePath<<endl;
	fout_log<<"max :"<<m_max<<endl;


	for(int i=0;i<m_max;i++)
	{
		m_pHitArea_Array[i].show();
	
	}

}

HitArea* HitAreaSet::getHitArea_P(int i)
{
	if(i>=0&&i<m_max)
	{
		if(m_pHitArea_Array[i].isInitialized())
		{
			return &m_pHitArea_Array[i];
		}
		else 
		{
			return NULL;
		}

	}
	else 
	{
		return NULL;
	}

}