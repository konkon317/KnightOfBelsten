#ifndef INCLUDE_ENEMY_H
#define INCLUDE_ENEMY_H

#include "actor.h"
#define AI_TYPE_MAX 3


enum AI_MODE
{
	AI_MODE_INACTIVE,
	AI_MODE_ACTIVE,
	AI_MODE_ACTIVE_2,
	AI_MODE_ACTIVE_3
};

class Enemy:public Actor
{
private:
	int m_aiType;
	bool m_BossFlag;

	sp_Actor m_spTarget;
	AI_MODE m_AiMode;

public :

	Enemy();
	virtual ~Enemy();

	
	//AI_MODE m_aiMode;

	void setBossFlag(int i){m_BossFlag=(i==1)?true:false;};
	bool getBossFlag()const{return m_BossFlag;}
	

	void update(sp_Actor spPlayer,listSpActor* pLSpActors);

	const Actor* getSpTarget()const{return m_spTarget.get();}
	AI_MODE getAiMode()const{return m_AiMode;}

	void setAiMode(AI_MODE aiMode){m_AiMode=aiMode;}
	void setTarget(sp_Actor target);
	
	void setAiType(int i){if(i>=1&&i<=AI_TYPE_MAX)m_aiType=i;}
	int getAiType()const{return m_aiType;}


};



#endif
