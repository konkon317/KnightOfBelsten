#include "random.h"

#include <iostream>
using namespace std;


CRand::CRand()
//呼び出された時刻をシード値に設定するコンストラクタ
	{
		m_Seed[0]=static_cast<unsigned long>(time(NULL));

		m_Seed[1]=12345;
		m_Seed[2]=987654321;
		m_Seed[3]=141592;
	}

CRand::CRand(unsigned long seed)
//定数をシード値に設定する 再現用
	{
		m_Seed[0]=seed;
		m_Seed[1]=12345;
		m_Seed[2]=987654321;
		m_Seed[3]=141592;
	}

CRand::CRand(unsigned long seed0,unsigned long seed1,unsigned long seed2,unsigned long seed3)
//記録された各シード値からクラスを再現するためのコンストラクタ 再現用
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
//乱数を生成し返す
	{
		unsigned long seed_t=(m_Seed[0]^(m_Seed[0]<<11));

		m_Seed[0]=m_Seed[1];
		m_Seed[1]=m_Seed[2];
		m_Seed[2]=m_Seed[3];

		m_Seed[3]= (m_Seed[3]^(m_Seed[3]>>19)) ^ (seed_t ^ (seed_t >> 8)); //乱数生成

		return m_Seed[3];//生成した乱数を返す
	}

unsigned long CRand::getRand(unsigned long Max)// 0<=Max の乱数を返す
	{
		return getRand()%Max;
	}

int CRand::getRand(int Max)// 0<=Max の乱数を返す
	{
		int reValue=static_cast<int>(getRand()%Max);
		return reValue;
	}



//---------------------------------------------------

void CRand::showSeed()//シード値をコンソールへ出力する
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
		if(!(i>=0&&i<4))//入力値が不当だったら
		{
			cout<< "CRand::getSeed 引数が不当です"<<endl;
			return 0;
		}
		else 
		{
			return m_Seed[i]; 
		}

	}

