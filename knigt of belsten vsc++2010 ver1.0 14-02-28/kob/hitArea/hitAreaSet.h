#ifndef INCLUDE_HITAREA_SET_H
#define INCLUDE_HITAREA_SET_H

#include "hitArea.h"
#include "../file/TexRead.h"
#include "../log.h"
//#include "../shared_ptr.h"
#include <string>

class HitAreaSet;

typedef boost::shared_ptr<HitAreaSet> SP_HitAreaSet;

class HitAreaSet
	//あたり判定情報をアニメーションのパターン数分セットにしたもの
{
private:

	int m_max;//hitAreaが何コマ分あるか
	char m_filePath[FILE_PATH_LENGTH];

	// _Arrayが付くポインタ変数は　配列でメモリ割り当てをする　解放にはSAFE_DELETE_ARRAY(p)を使用する
	HitArea * m_pHitArea_Array;
	//string * m_pFilePathToRead_Array;

	bool m_isInitialized;

public :
	HitAreaSet();
	~HitAreaSet();

	void initialize(const char * filePath);
	void show();

	void reset();

	bool isInitialized(){return m_isInitialized;}

	HitArea* getHitArea_P(int i);
};



#endif 