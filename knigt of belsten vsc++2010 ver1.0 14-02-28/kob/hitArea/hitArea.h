#ifndef INCLUDE_HITAREA_H
#define INCLUDE_HITAREA_H


#include "../file/TexRead.h"
#include "../defines.h"
#include "../log.h"

//�����蔻��̃G���A���@�~�̏W�܂�ŕ߂���
struct circle;

extern bool CheckHit_Circle(int x0,int y0,circle circle0,bool useTurnX0,
							int x1,int y1,circle circle1 ,bool useTurnX1);

struct circle
{
	int m_x;
	int m_y;
	int m_radius;//���a

	circle()//�R���X�g���N�^
	{
		m_x=m_y=m_radius=0;
	}

};


class HitArea
{
private :

	char m_filePath[FILE_PATH_LENGTH];
	int m_circleMax;

	bool m_bIsInitialized;

	circle* m_pCircle_Array;//_Array���t���|�C���^�ϐ��́@�z��Ń��������蓖�Ă�����@����ɂ�SAFE_DELETE_ARRAY(p)���g�p����

public:

	HitArea();
	~HitArea();

	void initialize(const char* filePath);

	circle getCircle(int i);

	void reset();

	bool isInitialized(){return m_bIsInitialized;}
	int getMax(){return m_circleMax;}

	void show();

};



#endif 