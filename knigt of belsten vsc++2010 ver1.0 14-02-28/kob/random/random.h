#ifndef INCLUDE_RANDOM_H
#define INCLUDE_RANDOM_H


#include <time.h>


class CRand// class randam  XorShift���g�p�����^�������N���X
{

private:
	unsigned long m_Seed[4];//�V�[�h�l	

public :
	CRand();//�Ăяo���ꂽ�������V�[�h�l�Ƃ���R���X�g���N�^

	CRand(unsigned long Seed);//�萔�V�[�h�p�R���X�g���N�^
	CRand(unsigned long seed0,unsigned long seed1,unsigned long seed2,unsigned long seed3);

	~CRand();

	unsigned long getRand();//�����𐶐����@�擾����
	unsigned long getRand(unsigned long Max);
	int getRand(int Max);

	void showSeed();//�V�[�h�l���R���\�[���֏o�͂���
	
	unsigned long getSeed(int i);//m_Seed[i]���擾����
};



#endif