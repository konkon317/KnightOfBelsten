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
	//�����蔻������A�j���[�V�����̃p�^�[�������Z�b�g�ɂ�������
{
private:

	int m_max;//hitArea�����R�}�����邩
	char m_filePath[FILE_PATH_LENGTH];

	// _Array���t���|�C���^�ϐ��́@�z��Ń��������蓖�Ă�����@����ɂ�SAFE_DELETE_ARRAY(p)���g�p����
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