#include "enemy.h"
#include "../ai/ai.h"
#include "../../sound/soundForDxLib.h"

Enemy::Enemy()
{
	m_animNum=m_animCount=0;
	m_mode=ACT_MODE_STAND;
	m_directionFacing=FACE_LEFT;
	m_AiMode =AI_MODE_INACTIVE;
	m_aiType=0;
	m_BossFlag=false;
}

//-------------------------------------------

Enemy::~Enemy()
{
	m_spTarget.reset();
}

//-------------------------------------------

void Enemy::update(sp_Actor spPlayer,listSpActor* pLSpActors)
{
	//アップデート	
	Actor::update();

	//aiの指向
	AiData aiData= think(this,m_spTarget,*pLSpActors);
	
	
	if(this->doseGetHit(spPlayer))//攻撃が当たったか
	{
		//ダメージ処理
		damage((spPlayer->getActorData()->getAtackPoint())-(m_spActData->getDefencePoint()));
		playSound("enemyDamage");
	}

	if(aiData.atackStartFlag&&(m_mode==ACT_MODE_STAND||m_mode==ACT_MODE_WALK))
	{
		//攻撃開始
		setMode(ACT_MODE_ATTACK_1);
		playSound("attack");
	}
	
	//座標移動
	move(aiData.moveX,aiData.moveY,pLSpActors);

	if(m_spTarget.get()!=NULL)
	{
		if(m_mode==ACT_MODE_STAND||m_mode==ACT_MODE_WALK)
		{
			//ターゲットのいる方向を向く
			if(m_x>m_spTarget->getX())m_directionFacing=FACE_LEFT;
			if(m_x<m_spTarget->getX())m_directionFacing=FACE_RIGHT;
		}
	}	

	updateOldPosition();
}

//-------------------------------------------

void Enemy::setTarget(sp_Actor target)
{
	//攻撃の対象を設定する
	m_spTarget=target;
}