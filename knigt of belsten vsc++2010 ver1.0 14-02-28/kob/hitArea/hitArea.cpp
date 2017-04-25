#include "hitArea.h"

#include <string>

#include "../log.h"

bool CheckHit_Circle(int x0,int y0,circle circle0,bool useTurnX0,
					 int x1,int y1,circle circle1,bool useTurnX1)
{
	//�~���m�̓��蔻����s���܂�
	//�ڐG���Ă���Ȃ�true


	//�摜�����E���]���Ă��邩
	if(useTurnX0)
	{
		circle0.m_x*=-1;
	}
	
	if(useTurnX1)
	{
		circle1.m_x*=-1;
	}

	int centerX0=x0+circle0.m_x;
	int centerY0=y0+circle0.m_y;

	int centerX1=x1+circle1.m_x;
	int centerY1=y1+circle1.m_y;

	int distanceX=(centerX0-centerX1);
	int distanceY=(centerY0-centerY1);


	//�O�����̒藝���g���ĉ~�̒��S���m�̋������r���܂�

	int distance =(distanceX*distanceX)+(distanceY*distanceY);//���ۂ̋���  ���m�ɂ͋����̓��
	int checkDistance=(circle0.m_radius+circle1.m_radius)*(circle0.m_radius+circle1.m_radius);//�Œ���G��Ă��鋗�� ���m�ɂ͋����̓��

	if(distance<checkDistance)
	{
		return true;
	}
	else 
	{
		return false;
	}

}

//----------------------------------------------------------------------

HitArea::HitArea()
{
	//�R���X�g���N�^

	m_circleMax=0;
	m_pCircle_Array=NULL;
	strcpy_s(m_filePath,"none");
	m_bIsInitialized=false;
}

//----------------------------------------------------------------------
HitArea::~HitArea()
{	
	//�f�X�g���N�^�ł�
	SAFE_DELETE_ARRAY(m_pCircle_Array);
}

//------------------------------------------------------------------------
void HitArea::reset()
{
	//�������̉�����s�����ׂĂ̕ϐ������Z�b�g���܂�
	SAFE_DELETE_ARRAY(m_pCircle_Array);
	
	m_circleMax=0;
	strcpy_s(m_filePath,"none");
	m_bIsInitialized=false;
	m_bIsInitialized=false;
}

//---------------------------------------------------------------------

circle HitArea::getCircle(int i)
{
	//�w�肳�ꂽ�Y�����̉~�f�[�^��Ԃ��܂�
	//���s���ɂ͂��ׂĒl��0�̂��̂�Ԃ��܂�

	circle r;
	if(i>=0&&i<m_circleMax&&m_bIsInitialized)
	{
		r=m_pCircle_Array[i];
	}

	return r;

}

//--------------------------------------------------------------------

void HitArea::initialize(const char* filePath)
{
	//�������֐�


	strcpy_s(m_filePath,filePath);
	
	fout_log<<endl;
	fout_log<<"hitArea initialize"<<endl;
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

	if(str!="<aMax>")//���e�ɊԈႢ������ꍇ
	{	
		return;	
	}

	
	//�~�̐���ǂݏo��
	getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

	m_circleMax=atoi(inputC);	//�~�̐����i�[

	//���������蓖��
	if(m_circleMax>0 && m_pCircle_Array==NULL)
	{
		m_pCircle_Array=new circle[m_circleMax];
	}
	
	for(int i=0;i<m_circleMax;i++)
	{
		//���C���̓ǂݏo���y�ѓǂݔ�΂��s�̔��f
		
		//texRead��Line���X�V�@�ǂݏo���̉ߒ��Ńt�@�C�����I�����Ă��Ȃ����̃`�F�b�N
		if(texRead.readLineSkipOverSolidus()==false)
		{
			cout<<"��蔭��"<<endl;	
			reset();
			return;
		}
		pLine=texRead.getLine();
		pos=0;
	
		int data[3];//x,y,r�̃f�[�^���i�[����

		for(int j=0;j<3;j++)
		{
			getNextStringToComma(inputC,pLine,&pos);//���̕������inputC�ɃR�s�[����@pLine[pos]����','�܂���'\n'�܂Ł@

			data[j]=atoi(inputC);
		}

		//�\���̂Ƀf�[�^���i�[����
		m_pCircle_Array[i].m_x=data[0];
		m_pCircle_Array[i].m_y=data[1];
		m_pCircle_Array[i].m_radius=data[2];	
	
	}

	m_bIsInitialized=true;

}

//-----------------------------------

void HitArea::show()
{
	//�f�o�b�O�p�̊֐�
	//�����o�ϐ��̒l���R���\�[�����ɏ����o���܂�

	fout_log<<m_filePath<<endl;
	fout_log<<"max :"<<m_circleMax<<endl;


	for(int i=0;i<m_circleMax;i++)
	{
		fout_log<< i<<" :"<<m_pCircle_Array[i].m_x<<","<<m_pCircle_Array[i].m_y<<","<<m_pCircle_Array[i].m_radius<<endl;

	}

}