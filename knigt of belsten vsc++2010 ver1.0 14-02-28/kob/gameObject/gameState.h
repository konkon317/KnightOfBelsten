#ifndef INCLUDE_GAMESTATE_H
#define INCLUDE_GAMESTATE_H

#include <vector>
#include <list>

#include "baseObject.h"
#include "actor/player.h"
#include "actor/enemy.h"

#include "actor/actorData.h"

#include "../defines.h"
//#include "../shared_ptr.h"
#include "../Input/InputForDxLib.h"
#include "../2DGraph/2DGraphForDxLib.h"
#include "../2DGraph/Draw2DForDxLib.h"

#include "map/map.h"

#include "interface/interface.h"

//#define ENEMY_MAX 10

enum GAME_SEQUENCE
{
	SEQ_LOGO,
	SEQ_INIT,
	SEQ_TITLE,
	SEQ_GAME,
	SEQ_OVER,
	SEQ_CLEAR,
	SEQ_TEAM_MORIMOTO
};


typedef list<spActorData> listSpActorData;

class GameState
{
private:

	bool m_bIsInitialized;//初期化されたかどうか

	int m_tBlendPar;//temporaryBlendParamater

	GAME_SEQUENCE m_sequence;
	

	//drawBuuferを分けているのレイヤーわけのため
	sp_DrawBuffer m_spDrawBufferFarEnd;
	sp_DrawBuffer m_spDrawBufferGameObject;
	sp_DrawBuffer m_spDrawBufferBackGround;
	
	sp_DrawBuffer m_spDrawBufferFront;	
	
	sp_DrawBuffer m_spDrawBufferShadow;
	sp_DrawBuffer m_spDrawBufferInterface;
		
	sp_Actor m_spPlayer;

	listSpActor m_lSpActors;

	listSpActorData m_lSpActorData;

	Input* m_pInput;

	Interface m_Interface;
	
	sp_Map m_spMap;
	
	sp_Graphics2D m_spGraphLogo;
	sp_Graphics2D m_spGraphTitle;
	sp_Graphics2D m_spGraphGameOver;
	sp_Graphics2D m_spGraphAllBlack;
	sp_Graphics2D m_spGraphClear;
	sp_Graphics2D m_spGraphTeamMorimoto;

	string m_bgmName;

public:

	GameState();//デフォルトコンストラクタ
	~GameState();

	void initialize(Input* pInput);

	void setDrawBuffer
		(sp_DrawBuffer spDrawBufferFarEnd,
		sp_DrawBuffer spDrawBufferBackGround,
		sp_DrawBuffer spDrawBufferFront,
		sp_DrawBuffer spDrawBufferGameObject,
		sp_DrawBuffer spDrawBufferShadow,
		sp_DrawBuffer spDrawBuufferInterface);

	void initializeActorData(char* filePath);

	spActorData findSpActorDataNamed(const char* name);

	bool isCleared();

	void initializeEnemy(const char * filePath);

	void setUpGame();

	void update();
	void updateGame();

	void drawSet();

	void changeBgm(const char* name);
	void stopBgm();
	//以下値を取得するだけのインライン関数
	GAME_SEQUENCE getSequence(){return m_sequence;}

	bool isInitialized(){return m_bIsInitialized;}




};

#endif
