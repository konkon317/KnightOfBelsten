//////////////////////
//	2013/7/18-7/19
//	���� �N��
//	Kousuke Fujii
//  �g�p���C�u�����@DX���C�u���� http://homepage2.nifty.com/natupaji/DxLib/
/////////////////////

#include "2DGraphForDxLib.h"
#include "DxLib.h"
#include "..\defines.h"

#include <iostream>
using namespace std;


//------------------------------------------------------------------------------

 void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath)
 {	
	//initialize shared_ptr Graphics
	//spGraph�Ő錾���ꂽ�I�u�W�F�N�g�ɑ΂���new�Ń��������蓖�Č�A�������֐����Ăяo��
	//���������蓖�Ă���摜���[�h�܂œ����ɍs�������ꍇ�Ɏg�p
	
	if(pSpGraph->get()==NULL)
	{
		(*pSpGraph)=sp_Graphics2D(new Graphics2D());//�I�u�W�F�N�g��new����
		
		if(pSpGraph->get()!=NULL)//���Ȃ�new ���ꂽ��
		{
		
			(*pSpGraph)->initialize(filePath);//�摜�̃��[�h
		}
	}
 }



 void initializeSpGraph(sp_Graphics2D* pSpGraph,char* filePath,int max,int xSize,int ySize,int xNum,int yNum)
 {		
	//initialize shared_ptr Graphics
	//spGraph�Ő錾���ꂽ�I�u�W�F�N�g�ɑ΂���new�Ń��������蓖�Č�A�������֐����Ăяo��
	//���������蓖�Ă���摜���[�h�܂œ����ɍs�������ꍇ�Ɏg�p
	//�������[�h�p�̃I�[�o�[���[�h

	if(pSpGraph->get()==NULL)
	{
		*pSpGraph=sp_Graphics2D(new Graphics2D());//�I�u�W�F�N�g��new����
		
		if(pSpGraph->get()!=NULL)//���Ȃ�new���ꂽ��
		{
			(*pSpGraph)->initialize(filePath,max,xSize,ySize,xNum,yNum);//�摜�̃��[�h
		}
	} 
 }

//�ȉ�Graphics2D �����o�֐�
//----------------------------------------------------------------------------
//�f�t�H���g�R���X�g���N�^
Graphics2D::Graphics2D()
{
	m_max=0;			//�摜�n���h���z��̐�
	m_xSize=m_ySize;	//loadDivGraph�ŕ����ǂݍ��݂���Ƃ��������̉摜�T�C�Y
	m_xNum=m_yNum;		//loadDivGraph�ŕ����ǂݍ��݂��鎞�̏c��������
	m_bIsInitialized=false;//����������Ă��邩
	
	for(int i=0;i<FILE_PATH_LENGTH;i++)
	{
		m_filePath[i]='\0';//�t�@�C���p�X
	}
	m_pHandleBuff=NULL;
}

//----------------------------------------------------------------------------
//�f�X�g���N�^
Graphics2D::~Graphics2D()
{
	cout<<"2DGraph�f�X�g���N�^ in "<<m_filePath<<endl;

	for(int i=0;i<m_max;i++)//�摜���폜����
	{
		DeleteGraph(m_pHandleBuff[i]);
		m_pHandleBuff[i]=-1;
	}

	SAFE_DELETE_ARRAY(m_pHandleBuff);//�������̉���� null������
}

//---------------------------------------------------------------------------
//�ȉ��R���X�g���N�^�A�f�X�g���N�^�ȊO�̊֐���`
//----------------------------------------------------------------------------

void Graphics2D::reset()
{
	//�f�t�H���g�R���X�g���N�^�ŏ��������ꂽ�Ƃ��Ɠ�����Ԃ�

	for(int i=0;i<m_max;i++)//�摜������������폜����
	{
		DeleteGraph(m_pHandleBuff[i]);
		m_pHandleBuff[i]=-1;
	}

	SAFE_DELETE_ARRAY(m_pHandleBuff);//�������̉���� null������

	//�����l�����Z�b�g
	m_max=0;		
	m_xSize=m_ySize;	
	m_xNum=m_yNum;		
	m_bIsInitialized=false;

	//�t�@�C���p�X�̃��Z�b�g
	for(int i=0;i<FILE_PATH_LENGTH;i++)
	{
		m_filePath[i]='\0';
	}
}

//----------------------------------------------------------------------

void Graphics2D::initialize(const char *filePath, int max, int xSize, int ySize, int xNum, int yNum)
{
	//�������֐� DxLib��LoadDivGraph�֐����g�p����ꍇ

	//cout<<"2DGraphInitialize in "<<filePath<<endl;
	if(!m_bIsInitialized)
	{
		strcpy_s(m_filePath,filePath);

		m_max=max;

		m_xSize=xSize;
		m_ySize=ySize;

		m_xNum=xNum;
		m_yNum=yNum;

		m_pHandleBuff=new int[m_max];//���������蓖
	
		if(!m_pHandleBuff)//���������蓖�ĂɎ��s�����ꍇ
		{
			m_max=0;//���Z�b�g�֐��Ō���ĉ摜�폜�����ɓ���Ȃ��悤�ɂ��邽�߂̏���
			//cout<<"���������蓖�Ď��s���܂���(loadDivGraph)"<<endl<<filePath<<endl;
			reset();
			return;
			//�f�[�^���Z�b�g�����^�[��
		}

		//�摜�̃��[�h
		int isLoaded=LoadDivGraph(m_filePath,m_max,m_xNum,m_yNum,m_xSize,m_ySize,m_pHandleBuff);

		if(isLoaded==-1)//�G���[�����Ȃ�
		{
			//cout<<"�摜�ǂݍ��݂Ɏ��s���܂���(loadDivGraph)"<<endl<<filePath<<endl;
			reset();
			return;
			//�f�[�^���Z�b�g�����^�[��
		}

		m_bIsInitialized=true;
	}
	else
	{
		//cout<<"���łɏ���������Ă���C���X�^���X�����������悤�Ƃ��܂���(div)-"<<filePath<<endl;
	}
	//cout<<"2DGraphInitialize out "<<endl<<endl;
}

//----------------------------------------------------------------------

void Graphics2D::initialize(const char *filePath)
{
	//�������֐� DxLib��LoadGraph�֐����g�p����ꍇ
	
	//cout<<"2DGraphInitialize in "<<filePath<<endl;

	if(!m_bIsInitialized)
	{
	strcpy_s(m_filePath,filePath);

	m_max=1;
	
	m_xNum=1;
	m_yNum=1;

	m_pHandleBuff=new int[m_max];//���������蓖

	if(!m_pHandleBuff)//���������蓖�ĂɎ��s�����ꍇ
	{
		m_max=0;//���Z�b�g�֐��Ō���ĉ摜�폜�����ɓ���Ȃ��悤�ɂ��邽�߂̏���
		//cout<<"���������蓖�ĂɎ��s���܂���(loadGraph)"<<endl<<filePath<<endl;
		reset();
		return;
		//�f�[�^���Z�b�g�����^�[��
	}
	m_pHandleBuff[0]=LoadGraph(m_filePath);//�摜�̃��[�h
	
	if(m_pHandleBuff[0]==-1)//�G���[�����̏ꍇ
	{
		//cout<<"�摜�ǂݍ��݂Ɏ��s���܂���(loadGraph)"<<endl<<filePath<<endl;
		reset();
		return;
		//�f�[�^���Z�b�g�����^�[��
	}

	GetGraphSize(m_pHandleBuff[0],&m_xSize,&m_ySize);
	m_bIsInitialized=true;
	}
	else
	{
		//cout<<"���łɏ���������Ă���C���X�^���X�����������悤�Ƃ��܂���-"<<filePath<<endl;
	}

	//cout<<"2DGraphInitialize out "<<endl<<endl;
}

//----------------------------------------------------------------------


int Graphics2D::getHandle(int num)const
{
	//�n���h�����擾���邽�߂̊֐�
	if(m_bIsInitialized)
	{
		if(num>=0&&num<m_max)
		{
			return m_pHandleBuff[num];
		}
	}	
	return -1;//DXLIB�Ŏ��s�������߂�l�@
}

