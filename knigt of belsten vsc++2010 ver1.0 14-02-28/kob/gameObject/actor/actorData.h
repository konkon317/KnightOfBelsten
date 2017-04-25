#ifndef INCLUDE_ACTOR_DATA_H
#define INCLUDE_ACTOR_DATA_H

#include <iostream>
#include <string>

using namespace std;

#include "../../defines.h"
#include "../../log.h"
#include "../../file/TexRead.h"
#include "../../2DGraph/2DGraphForDxLib.h"
#include "../../hitArea/hitAreaSet.h"

class ActorData;

typedef boost::shared_ptr<ActorData> spActorData;

struct GraphPatternData
{
	int m_sheetNum;//�����ڂ̃V�[�g��
	int m_index;
	int m_max;

	GraphPatternData()
	{
		m_sheetNum=m_index=m_max=0;
	}
};


//�X�e�[�^�X�Ƃ����蔻��̏��A�O���t�B�b�N����܂Ƃ߂ɂ����N���X�ł�
class ActorData
{
private:
	bool m_bIsInitialized;

	string m_filePath;
	int m_GraphMax;//�����̉摜�V�[�g���g�p����L�����N�^�[��

	int m_modeMax;


	int m_sizeX;
	int m_sizeZ;


	int m_maxHp;
	double m_speedLR;
	double m_speedZ;

	int m_atackRangeX;
	int m_atackRangeZ;
	int m_atackPoint;
	int m_defencePoint;

	string m_name;

	HitAreaSet m_hitAreaSet;
	string m_filePathForHitArea;

	HitAreaSet m_atackAreaSet;
	string m_filePathForAtackArea;


	Graphics2D * m_pGraph2D_Arr;				// _arr���t���Ɣz��Ń������m�ہ@SAFE_DELETE_ARRAY�ŉ������ m_GraphMax�������m��
	Graphics2D * m_pGraph2D_Shadow_Arr;			// _arr���t���Ɣz��Ń������m�ہ@SAFE_DELETE_ARRAY�ŉ������ m_GraphMax�������m��
	
	string * m_pFilePathForGraph_Arr;			// _arr���t���Ɣz��Ń������m�ہ@SAFE_DELETE_ARRAY�ŉ������ m_GraphMax�������m��
	string * m_pFilePathForGraph_Shadow_Arr;	// _arr���t���Ɣz��Ń������m�ہ@SAFE_DELETE_ARRAY�ŉ������ m_GraphMax�������m��

	GraphPatternData* m_pGraphPatternData_Arr;	// _arr���t���Ɣz��Ń������m�ہ@SAFE_DELETE_ARRAY�ŉ������ m_modeMax�������m��

public :

	ActorData();
	~ActorData();

	void reset();

	void initialize(const char* filePath);	

	void show();

	bool isInitialized(){return m_bIsInitialized;}

	HitAreaSet* getHitAreaSet_P(){return &m_hitAreaSet;}
	HitAreaSet* getAtackAreaSet_P(){return &m_atackAreaSet;}

	int getSizeX()const{return m_sizeX;}
	int getSizeZ()const{return m_sizeZ;}
	
	int getMaxHp()const{return m_maxHp;}
	double getSpeedLR()const{return m_speedLR;}
	double getSpeedZ()const{return m_speedZ;}

	int getGraphMax()const{return m_GraphMax;}
	int getGraphMaxInSheet(int i)const;

	int getAtackRangeZ()const{return m_atackRangeZ;}
	int getAtackRangeX()const{return m_atackRangeX;}

	int getAtackPoint()const{return m_atackPoint;}
	int getDefencePoint()const{return m_defencePoint;}

	string getName()const{return m_name;}

	GraphPatternData getGraphPatternData(int i)const;

	Graphics2D * getPGraph(int i);
	Graphics2D * getPGraphShadow(int i);
};

#endif 