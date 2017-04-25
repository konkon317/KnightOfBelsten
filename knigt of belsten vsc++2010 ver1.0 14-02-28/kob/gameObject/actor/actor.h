#ifndef INCLUDE_ACTOR_H
#define INCLUDE_ACTOR_H

#include "../baseObject.h"
#include <list>

#include "../../defines.h"
//#include "../shared_ptr.h"
#include "../../Input/InputForDxLib.h"
#include "../../2DGraph/2DGraphForDxLib.h"
#include "../../2DGraph/Draw2DForDxLib.h"

#include "actorData.h"

#include "../map/map.h"

#define SPEED_LR 3.0
#define SPEED_Z 1.5

#define ACT_MODE_MAX 6


#define ANIM_COUNT_MAX 10 //アニメーションの同じ一コマを表示し続けるフレーム数　
#define INTERVAL_OF_DAMAGE_MAX  ANIM_COUNT_MAX*3

class Actor;
typedef boost::shared_ptr<Actor> sp_Actor;
typedef list<sp_Actor> listSpActor;

enum DIRECTION_FACING
{
	
	FACE_RIGHT,
	FACE_LEFT

};

enum ACTOR_MODE
{
	ACT_MODE_STAND=0,
	ACT_MODE_WALK=1,
	ACT_MODE_ATTACK_1=2,

	ACT_MODE_JUMP=5,

	ACT_MODE_DAMAGE=3,
	ACT_MODE_DIE=4,

};

class Actor:public BaseObject
{

protected:
	int m_animNum;
	int m_animCount;

	int m_hitPoint;

	int m_countIntervalOfDamage;

	int m_firstX;
	int m_firstZ;

	int m_moveXMax;
	int	m_moveXMin;

	double m_oldX;
	double m_oldY;
	double m_oldZ;

	ACTOR_MODE m_mode;

	DIRECTION_FACING m_directionFacing;//向いている方向

	spActorData m_spActData;

	sp_Map m_spMap;

public:

	Actor();
	virtual ~Actor();

	//----------------------------------------------
	//値または状態を取得する関数	
	
	bool getTurnFlag(){return (m_directionFacing==FACE_LEFT)?true:false;}

	HitArea* getHitAreaBody_P()const;
	HitArea* getAtackArea_P()const;

	bool isDead()const;		

	//インライン関数
	
	ActorData* getActorData()const {return m_spActData.get();}
	
	double getOldX()const{return m_oldX;}
	double getOldY()const{return m_oldY;}
	double getOldZ()const{return m_oldZ;}

	int getFirstX()const{return m_firstX;}
	int getFirstZ()const{return m_firstZ;}
	
	int getMoveXMax()const{return m_moveXMax;}
	int getMoveXMin()const{return m_moveXMin;}

	int getAnimNum()const{return m_animNum;}
	int getAnimCount()const{return m_animCount;}

	int getHp()const{return m_hitPoint;}

	int getCountIntervalOfDamage(){return m_countIntervalOfDamage;}

	ACTOR_MODE getActorMode()const{return m_mode;}
	DIRECTION_FACING getDirectionFacing()const{return m_directionFacing;}

	//仮想関数

	virtual int getAiType()const{return 0;}
	virtual bool getBossFlag()const{return false;}

	//---------------------------------------------------
	//値を設定する関数
	
	void setFirstPosition(double x,double y);
	void setMode(ACTOR_MODE actMode);	
	void setPosition(double x,double y,double z);
	void updateOldPosition();						//1フレーム前の座標を保持する

	void setActerData(spActorData spActData);
	void setMap(sp_Map spMap);
	void setHp(int point);
	void setHpMax();
	
	//インライン関数
	void setPositionXOld(){m_x=m_oldX;}
	void setPositionZOld(){m_z=m_oldZ;}
	void setMoveMaxAndMIN(int max,int min){m_moveXMax=max;m_moveXMin=min;};

	//仮想関数

	virtual void setTarget(sp_Actor target){}
	virtual void setAiType(int i){}
	virtual void setBossFlag(int i){};	

	//--------------------------------------------------------
	//実行してもメンバ変数に変更が無い関数

	bool isBrashedWith(Actor* actor)const;
	bool isBrashedWithSomeOne(listSpActor* lSpActors)const;	
	
	bool doseGetHit(sp_Actor spActor)const;
	void drawSet(int scrollX)const;

	//----------------------------------------------------------
	//実行するとメンバ変数の更新が伴う可能性があるもの

	virtual void update();
	virtual void move(double x,double z,listSpActor* plspActors);
	
	void damage(int point);	

	void updateAnimation();	
	
	void updateCountIntervalOfDamage();	

	void kill(){damage(99999);}


	//仮想関数
	virtual void update(Input* pInput,listSpActor* plspActors){}
	virtual void update(sp_Actor spPlayer,listSpActor* plSpActors){}
	
	virtual void reset(){};

	

	
	

	
};

#endif