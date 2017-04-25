#include "player.h"
#include "../../sound/soundForDxLib.h"
/*
#define SPEED_LR 1.5
#define SPEED_Z 1.0*/

#define PLAYER_MODE_MAX 3

const int GraphMax[PLAYER_MODE_MAX]={3,4,3};
const int GraphIndex[PLAYER_MODE_MAX]={0,3,7};

//--------------------------------------------------
Player::Player()
{
	m_animNum=m_animCount=0;
	m_mode=ACT_MODE_STAND;
	m_directionFacing=FACE_RIGHT;
}

//--------------------------------------------------

Player::~Player()
{

}

//--------------------------------------------------

void Player::reset()
{
	//初期値に戻す

	m_animNum=m_animCount=0;
	m_mode=ACT_MODE_STAND;
	m_directionFacing=FACE_RIGHT;

	Actor::setHpMax();
	setPosition(getFirstX(),0,getFirstZ());
	setMoveMaxAndMIN(-1,-1);
}

//---------------------------------------------------

void Player::move(Input* pInput,listSpActor* plspActors)
{
	//移動
	double moveX=0;
	double moveZ=0;	

	if(pInput->PadCt(0,PAD_LEFT)>=1&&pInput->PadCt(0,PAD_RIGHT)==0)
	{
		moveX=-1;
	}
	
	if(pInput->PadCt(0,PAD_RIGHT)>=1&&pInput->PadCt(0,PAD_LEFT)==0)
	{
		moveX=1;
	}

	if(pInput->PadCt(0,PAD_UP)>=1&&pInput->PadCt(0,PAD_DOWN)==0)
	{
		moveZ=1;
	}
	
	if(pInput->PadCt(0,PAD_DOWN)>=1&&pInput->PadCt(0,PAD_UP)==0)
	{
		moveZ=-1;
	}

	Actor::move(moveX,moveZ,plspActors);
}

//--------------------------------------------------

void Player::update(Input* pInput,listSpActor* pLSpActors)
{	
	//プレイヤーの更新
	//あたり判定　ダメージ処理　入力に対しての処理

	Actor::update();

	if(!(pLSpActors->empty()))
	for(listSpActor::iterator itr =pLSpActors->begin();itr!=pLSpActors->end();itr++)
	{
		if((*itr).get()!=NULL)
		{
		
			if((*itr).get()!=this)
			{
				if(doseGetHit(*itr))//攻撃が当たったか
				{
					if(Actor::getCountIntervalOfDamage()==0)
					{
						playSound("playerDamage");
					}
					
					damage(((*itr)->getActorData()->getAtackPoint())-(m_spActData->getDefencePoint()));
					
				}
			}
		}
	}


	if(m_mode==ACT_MODE_WALK||m_mode==ACT_MODE_STAND)
	{
		//プレイヤーの向きの更新
		//進行方向を向くようにする
		if(pInput->PadCt(0,PAD_LEFT)>=1&&pInput->PadCt(0,PAD_RIGHT)==0)
		{
			m_directionFacing=FACE_LEFT;
		}

		if(pInput->PadCt(0,PAD_RIGHT)>=1&&pInput->PadCt(0,PAD_LEFT)==0)
		{
			m_directionFacing=FACE_RIGHT;
		}

		//攻撃を開始する処理
		if(pInput->PadCt(0,PAD_BUTTON_A)==1)
		{
			m_mode=ACT_MODE_ATTACK_1;
			playSound("attack");
			m_animCount=0;
			m_animNum=0;
		}
	}


	if(m_mode==ACT_MODE_STAND||m_mode==ACT_MODE_WALK)
	{
		//座標移動
		//攻撃中、ダメージモーション中は移動できない
		move(pInput,pLSpActors);
	}
}