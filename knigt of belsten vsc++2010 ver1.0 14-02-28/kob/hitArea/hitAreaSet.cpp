#include "hitAreaSet.h"
#include "../log.h"

HitAreaSet::HitAreaSet()
{
	fout_log<<"hitAreaSet �R���X�g���N�^"<<endl;
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
	fout_log<<"hitAreaSet �f�X�g���N�^ "<<m_filePath<<endl;
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

	int pos=0;//���ǂ�ł���ʒu
	pLine=texRead.readLine();
	
	getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

	str=inputC;

	if(str!="<pMax>")//���e�ɊԈႢ������ꍇ
	{	
		return;	
	}

	
	//�R�}�̐���ǂ݂���
	getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

	m_max=atoi(inputC);	//�R�}�̐����i�[

	if(m_max>0&&m_pHitArea_Array==NULL)
	{
		m_pHitArea_Array=new HitArea[m_max];	
	}

	string filepath="noData";

	for(int i=0;i<m_max;i++)
	{
		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
	
		getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

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