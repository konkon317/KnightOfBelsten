#include "backGround.h"


//---------------------------------------------------------
//�f�t�H���g�R���X�g���N�^
BackGround::BackGround()
{	
	
}

//---------------------------------------------------------
//�f�X�g���N�^
BackGround::~BackGround()
{
	//����
	//�|�C���^����new,�t�@�C���I�[�v���Ȃ�	
	//����
}

//---------------------------------------------------------
//������
void BackGround::initialize(sp_DrawBuffer spBuff)
{
	++spBuff;//shared_ptr �Q�ƃJ�E���g�X�V

	m_spDrawBuffer=spBuff;
	m_spGraphBackGround_0.setName("backGround.png");
	m_spGraphBackGround_1.setName("load.png");

	
	initializeSpGraph(&m_spGraphBackGround_0,"images/backGround.png");
	initializeSpGraph(&m_spGraphBackGround_1,"images/load.png");
}


//---------------------------------------------------------
//�`��Z�b�g
void BackGround::drawSet(int scrollX)
{
	static double ex=0.0;
	


/*
for(int i=0;i<2;i++)
{	int setX=(WINDOW_WIDTH/2)+(i*WINDOW_WIDTH);
	double x=0;

	x=(0.5*(setX-(scrollX+(WINDOW_WIDTH/2))));
	m_spDrawBuffer->DrawSetCenterBottom(m_spGraphBackGround_0.getPointerReference(),0,static_cast<int>(setX-(scrollX+x)),300,ex,1.0,false);
}*/
	int x=static_cast<int>(0.7*scrollX);
	while(x>WINDOW_WIDTH)
	{
		x-=WINDOW_WIDTH;
	}

	m_spDrawBuffer->DrawSetLeftBottom(m_spGraphBackGround_0.getPointerReference(),0,-x,300,ex,1.0,false);
	m_spDrawBuffer->DrawSetLeftBottom(m_spGraphBackGround_0.getPointerReference(),0,-x+WINDOW_WIDTH,300,ex,1.0,false);

	m_spDrawBuffer->DrawSet(m_spGraphBackGround_1.getPointerReference(),0,-scrollX,458,false);

}