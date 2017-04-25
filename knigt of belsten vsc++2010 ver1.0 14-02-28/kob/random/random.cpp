#include "random.h"

#include <iostream>
using namespace std;


CRand::CRand()
//�Ăяo���ꂽ�������V�[�h�l�ɐݒ肷��R���X�g���N�^
	{
		m_Seed[0]=static_cast<unsigned long>(time(NULL));

		m_Seed[1]=12345;
		m_Seed[2]=987654321;
		m_Seed[3]=141592;
	}

CRand::CRand(unsigned long seed)
//�萔���V�[�h�l�ɐݒ肷�� �Č��p
	{
		m_Seed[0]=seed;
		m_Seed[1]=12345;
		m_Seed[2]=987654321;
		m_Seed[3]=141592;
	}

CRand::CRand(unsigned long seed0,unsigned long seed1,unsigned long seed2,unsigned long seed3)
//�L�^���ꂽ�e�V�[�h�l����N���X���Č����邽�߂̃R���X�g���N�^ �Č��p
	{
		m_Seed[0]=seed0;
		m_Seed[1]=seed1;
		m_Seed[2]=seed2;	
		m_Seed[3]=seed3;	
	}


//---------------------------------------------------

CRand::~CRand()
	{
		
	}

//---------------------------------------------------

unsigned long CRand::getRand()
//�����𐶐����Ԃ�
	{
		unsigned long seed_t=(m_Seed[0]^(m_Seed[0]<<11));

		m_Seed[0]=m_Seed[1];
		m_Seed[1]=m_Seed[2];
		m_Seed[2]=m_Seed[3];

		m_Seed[3]= (m_Seed[3]^(m_Seed[3]>>19)) ^ (seed_t ^ (seed_t >> 8)); //��������

		return m_Seed[3];//��������������Ԃ�
	}

unsigned long CRand::getRand(unsigned long Max)// 0<=Max �̗�����Ԃ�
	{
		return getRand()%Max;
	}

int CRand::getRand(int Max)// 0<=Max �̗�����Ԃ�
	{
		int reValue=static_cast<int>(getRand()%Max);
		return reValue;
	}



//---------------------------------------------------

void CRand::showSeed()//�V�[�h�l���R���\�[���֏o�͂���
	{
		cout<<"SEED 0 : "<<m_Seed[0]<<endl;
		cout<<"SEED 1 : "<<m_Seed[1]<<endl;
		cout<<"SEED 2 : "<<m_Seed[2]<<endl;
		cout<<"SEED 3 : "<<m_Seed[3]<<endl;
	
		cout<<endl;
	}

//---------------------------------------------------

unsigned long CRand::getSeed(int i)
	{
		if(!(i>=0&&i<4))//���͒l���s����������
		{
			cout<< "CRand::getSeed �������s���ł�"<<endl;
			return 0;
		}
		else 
		{
			return m_Seed[i]; 
		}

	}

