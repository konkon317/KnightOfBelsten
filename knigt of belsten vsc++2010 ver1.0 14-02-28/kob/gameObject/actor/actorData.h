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
	int m_sheetNum;//何枚目のシートか
	int m_index;
	int m_max;

	GraphPatternData()
	{
		m_sheetNum=m_index=m_max=0;
	}
};


//ステータスとあたり判定の情報、グラフィックを一まとめにしたクラスです
class ActorData
{
private:
	bool m_bIsInitialized;

	string m_filePath;
	int m_GraphMax;//何枚の画像シートを使用するキャラクターか

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


	Graphics2D * m_pGraph2D_Arr;				// _arrが付くと配列でメモリ確保　SAFE_DELETE_ARRAYで解放する m_GraphMax分だけ確保
	Graphics2D * m_pGraph2D_Shadow_Arr;			// _arrが付くと配列でメモリ確保　SAFE_DELETE_ARRAYで解放する m_GraphMax分だけ確保
	
	string * m_pFilePathForGraph_Arr;			// _arrが付くと配列でメモリ確保　SAFE_DELETE_ARRAYで解放する m_GraphMax分だけ確保
	string * m_pFilePathForGraph_Shadow_Arr;	// _arrが付くと配列でメモリ確保　SAFE_DELETE_ARRAYで解放する m_GraphMax分だけ確保

	GraphPatternData* m_pGraphPatternData_Arr;	// _arrが付くと配列でメモリ確保　SAFE_DELETE_ARRAYで解放する m_modeMax分だけ確保

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