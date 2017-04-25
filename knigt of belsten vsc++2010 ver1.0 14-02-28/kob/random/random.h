#ifndef INCLUDE_RANDOM_H
#define INCLUDE_RANDOM_H


#include <time.h>


class CRand// class randam  XorShiftを使用した疑似乱数クラス
{

private:
	unsigned long m_Seed[4];//シード値	

public :
	CRand();//呼び出された時刻をシード値とするコンストラクタ

	CRand(unsigned long Seed);//定数シード用コンストラクタ
	CRand(unsigned long seed0,unsigned long seed1,unsigned long seed2,unsigned long seed3);

	~CRand();

	unsigned long getRand();//乱数を生成し　取得する
	unsigned long getRand(unsigned long Max);
	int getRand(int Max);

	void showSeed();//シード値をコンソールへ出力する
	
	unsigned long getSeed(int i);//m_Seed[i]を取得する
};



#endif