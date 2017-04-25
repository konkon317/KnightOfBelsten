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
	//�A�b�v�f�[�g	
	Actor::update();

	//ai�̎w��
	AiData aiData= think(this,m_spTarget,*pLSpActors);
	
	
	if(this->doseGetHit(spPlayer))//�U��������������
	{
		//�_���[�W����
		damage((spPlayer->getActorData()->getAtackPoint())-(m_spActData->getDefencePoint()));
		playSound("enemyDamage");
	}

	if(aiData.atackStartFlag&&(m_mode==ACT_MODE_STAND||m_mode==ACT_MODE_WALK))
	{
		//�U���J�n
		setMode(ACT_MODE_ATTACK_1);
		playSound("attack");
	}
	
	//���W�ړ�
	move(aiData.moveX,aiData.moveY,pLSpActors);

	if(m_spTarget.get()!=NULL)
	{
		if(m_mode==ACT_MODE_STAND||m_mode==ACT_MODE_WALK)
		{
			//�^�[�Q�b�g�̂������������
			if(m_x>m_spTarget->getX())m_directionFacing=FACE_LEFT;
			if(m_x<m_spTarget->getX())m_directionFacing=FACE_RIGHT;
		}
	}	

	updateOldPosition();
}

//-------------------------------------------

void Enemy::setTarget(sp_Actor target)
{
	//�U���̑Ώۂ�ݒ肷��
	m_spTarget=target;
}