#include "ai.h"
#include <math.h>

AiData Crimp(Enemy* pEnemy,const Actor* pTarget);


AiData thinkType1( Enemy * pEnemy,const Actor* pPlayer,const listSpActor& pLSpActors);//単純に追いかけて攻撃してくるai
AiData thinkType2( Enemy * pEnemy,const Actor* pPlayer,const listSpActor& pLSpActors);//プレイヤーの進行を妨害するような動き
AiData thinkType3(Enemy * pEnemy,const Actor* pPlayer,const listSpActor& pLSpActors);//ボス用のAi

AiData GoToPoint(Enemy *pEnemy,int x,int z);

AiData  ForrowTirget( Enemy * pEnemy,const Actor* pTarget);
AiData dodge(Enemy *pEnemy ,const Actor* pTarget);
bool decideAttackStartType1(Enemy * pEnemy,const Actor* pTarget);//目の前に攻撃対象がいるならtrue

bool doesTargetStartAttack(const Actor* pTarget);

bool serchType1(Enemy * pEnemy,const Actor* pPlayer,int Range);


//Aiのスイッチ切りかえを行う関数
AiData think(Enemy * pEnemy,const sp_Actor spPlayer,const listSpActor& rLSpActors)
{
	//returnするDataには　移動方向　攻撃モーションをスタートするかのflagを格納する
	//思考ルーチンをスイッチで切りかえる関数
	AiData Data;

	switch(pEnemy->getAiType())
	{
	case 1:
		Data=thinkType1(pEnemy,spPlayer.get(),rLSpActors);
		break;
	case 2:
		Data=thinkType2(pEnemy,spPlayer.get(),rLSpActors);
		break;
	case 3:
		Data=thinkType3(pEnemy,spPlayer.get(),rLSpActors);
	
	}

	return Data;
}

//-------------------------

AiData thinkType1(Enemy * pEnemy,const Actor* pPlayer,const listSpActor& rLSpActors)
{
	//単純に追いかけて攻撃してくるai
	AiData Data;

	AI_MODE aiMode=pEnemy->getAiMode();
	switch(aiMode)
	{
		case AI_MODE_ACTIVE:
		{		
			Data=ForrowTirget(pEnemy,pEnemy->getSpTarget());
			
			Data.atackStartFlag=decideAttackStartType1(pEnemy,pEnemy->getSpTarget());
		}
		break;

		case AI_MODE_INACTIVE:
		{
			if(serchType1(pEnemy,pPlayer,400))
			{
				pEnemy->setAiMode(AI_MODE_ACTIVE);
			}
		}
		break;
	}

	return Data;
}

//-------------------------

AiData thinkType2(Enemy * pEnemy,const Actor* pPlayer,const listSpActor& rLSpActors)
{
	//プレイヤーの進行を妨害するような動き
	AiData Data;

	AI_MODE aiMode=pEnemy->getAiMode();
	switch(aiMode)
	{
		case AI_MODE_ACTIVE:
		{
		
			Data=Crimp(pEnemy,pEnemy->getSpTarget());
			Data.atackStartFlag=decideAttackStartType1(pEnemy,pEnemy->getSpTarget());
		}
		break;

		case AI_MODE_INACTIVE:
		{

			if(serchType1(pEnemy,pPlayer,300))
			{
				pEnemy->setAiMode(AI_MODE_ACTIVE);
			}
		}
		break;
	}

	return Data;
}

//-------------------------

AiData thinkType3(Enemy * pEnemy,const Actor* pPlayer,const listSpActor& rLSpActors)
{
	//ボス用のAI
	AiData Data;

	AI_MODE aiMode=pEnemy->getAiMode();
	switch(aiMode)
	{
		case AI_MODE_ACTIVE:
		{
			const Actor* pTarget=pEnemy->getSpTarget();
			if(pTarget!=NULL)
			{
				Data=ForrowTirget(pEnemy,pTarget);
		
				if(doesTargetStartAttack(pEnemy->getSpTarget()))
				{
					pEnemy->setAiMode(AI_MODE_ACTIVE_2);
				}
		
				Data.atackStartFlag=decideAttackStartType1(pEnemy,pEnemy->getSpTarget());
			}
		}
		break;

		case AI_MODE_ACTIVE_2:
			{
				const Actor* pTarget=pEnemy->getSpTarget();
				if(pTarget!=NULL)
				{
					if(pTarget->getActorMode()!=ACT_MODE_ATTACK_1)
					{
						pEnemy->setAiMode(AI_MODE_ACTIVE);
					}
					else
					{
						Data=dodge(pEnemy,pTarget);	
					}
				}
				else
				{
					pEnemy->setAiMode(AI_MODE_INACTIVE);
				}
			}

			break;

		case AI_MODE_ACTIVE_3:

			break;

		case AI_MODE_INACTIVE:
		{

			if(serchType1(pEnemy,pPlayer,800))
			{
				pEnemy->setAiMode(AI_MODE_ACTIVE);
			}
		}
		break;
	}

	return Data;
}

//-------------------------

AiData GoToPoint(Enemy* pEnemy,int x,int z)
{
	//指定したポイントへ移動させるためのAi
	AiData Data;

	int myX=static_cast<int>(pEnemy->getX());
	int myZ=static_cast<int>(pEnemy->getZ());

	double r=atan2((-myX)+x,static_cast<double>(z-myZ));
	if(x>myX+10||x<myX-10)
	{
		Data.moveX=sin(r);
	}
	if(z>myZ+10||z<myZ-10)
	{
		Data.moveY=cos(r);
	}

	return Data;
}

//-------------------------


AiData Crimp(Enemy* pEnemy,const Actor* pTarget)
{
	//妨害する動き本体
	
	AiData Data;

	if(pTarget!=NULL)
	{

	int myX=static_cast<int>(pEnemy->getX());
	int myZ=static_cast<int>(pEnemy->getZ());
	
	int targetX=static_cast<int>(pTarget->getX());
	int targetZ=static_cast<int>(pTarget->getZ());

	if(pEnemy->getFirstX()<targetX)
	{
		pEnemy->setAiType(1);
	}
	else 
	{
		if(!(myZ+10>targetZ&&myZ-10<targetZ))
		{
			if(serchType1(pEnemy,pTarget,300))
			{
				double r=atan2(0.0,static_cast<double>(targetZ-myZ));
				Data.moveX=sin(r);
				Data.moveY=cos(r);
			}
		}
	}
	}

return Data;

}

//-------------------------

bool doesTargetStartAttack(const Actor* pTarget)
{
	//攻撃を開始するかどうか判断させる
	bool r=false;

	if(pTarget!=NULL)
	{
		if(pTarget->getActorMode()==ACT_MODE_ATTACK_1)
		{
			if(pTarget->getAnimNum()==0)
			{
				if(pTarget->getAnimCount())
				{
					r=true;
				}
			}
		}
	}
	return r;
}

//-------------------------

AiData dodge(Enemy* pEnemy,const Actor* pTarget)
{
	//ターゲットからの攻撃を回避するような動きをさせるAI

	AiData Data;
	if(pTarget!=NULL)
	{
		int movePointZ_1=static_cast<int>(pTarget->getZ()+(pTarget->getActorData()->getAtackRangeZ()/2)+(pEnemy->getActorData()->getSizeZ()/2+20));
		int movePointZ_2=static_cast<int>(pTarget->getZ()-(pTarget->getActorData()->getAtackRangeZ()/2)+(pEnemy->getActorData()->getSizeZ()/2+20));

		int distance1=static_cast<int>(movePointZ_1-pEnemy->getZ());
		int distance2=static_cast<int>(movePointZ_2-pEnemy->getZ());

		if(distance1<0)distance1*=-1;
		if(distance2<0)distance2*=-1;

		int pointZ=static_cast<int>(pEnemy->getZ());

		if(distance1<distance2)
		{
			if(movePointZ_1>MOVE_MAX_Z)pointZ=movePointZ_2;
			else pointZ=movePointZ_1;			
		}
		else
		{			
			if(movePointZ_2<MOVE_MIN_Z)pointZ=movePointZ_1;
			else pointZ=movePointZ_2;
		}
		
		if((pEnemy->getZ()>movePointZ_2)&&(pEnemy->getZ()<movePointZ_1))
		{		
			

			double r=atan2(0.0,static_cast<double>(pointZ-pEnemy->getZ()));
			
			Data.moveY=cos(r);	
		}

		{
			int xDistance=static_cast<int>(pEnemy->getX()-pTarget->getX());
			if(xDistance<0)xDistance*=-1;

			double d=1;
			if(pEnemy->getDirectionFacing()==FACE_RIGHT)d*=-1;
			if(xDistance<250)Data.moveX=sin(d);
		}
	}
	return Data;
}

//-------------------------

bool serchType1(Enemy * pEnemy,const Actor* pPlayer,int Range)//
{
	//プレイヤーが自分から一定の距離以内に居るか
	int myX=static_cast<int>(pEnemy->getX());
	int playerX=static_cast<int>(pPlayer->getX());
	
	if(Range>0)
	{
		if(myX-Range<playerX)
		{
			return true;		
		}
	}	
	return false;
}

//-------------------------

AiData ForrowTirget(Enemy* pEnemy,const Actor* pTarget)
{
	
	//雑魚のAI　追いかけるように移動する
	
	AiData Data;
	
	if(pTarget!=NULL)
	{
		
		if(!(pTarget->isDead()))
		{
			double targetX=pTarget->getX();
			double targetZ=pTarget->getZ();

			int targetSizeX=(pTarget->getActorData()->getSizeX()/2);
			int mySizeX=(pEnemy->getActorData()->getSizeX()/2);

			double myX=pEnemy->getX();
			double myZ=pEnemy->getZ();

			double targetXLow=targetX-(targetSizeX+mySizeX+10);
			double targetXHigh=targetX+(targetSizeX+mySizeX+10);

			double distanceForHighX=(targetXHigh-myX)*(targetXHigh-myX)+(targetZ-myZ)*(targetZ-myZ);
			double distanceForLowX=(targetXLow-myX)*(targetXLow-myX)+(targetZ-myZ)*(targetZ-myZ);

			if(distanceForHighX<=distanceForLowX)
			{
				targetX=targetXHigh;
			}
			else
			{
				targetX=targetXLow;
			}

			double r=atan2(targetX-myX,targetZ-myZ);
			Data.moveX=sin(r);
			Data.moveY=cos(r);		
		}
	}
	return Data;
}

//-------------------------

bool decideAttackStartType1(Enemy * pEnemy,const Actor* pTarget)
{
	//目の前にターゲットがいるならTrueを返す 攻撃モーションをスタートさせるか決定する時に用いる
	
	bool r=false;

	if(pTarget!=NULL)
	{
		if(!(pTarget->isDead()))
		{
			int targetSizeX=(pTarget->getActorData()->getSizeX()/2);
			int targetSizeZ=static_cast<int>(pTarget->getActorData()->getSizeZ()/2);
			int mySizeX=(0.8*pEnemy->getActorData()->getSizeX()/2);
			int mySizeZ=(0.8*pEnemy->getActorData()->getSizeZ()/2);
			//double targetLowX=spTarget->getActorData()->getSizeX();			

			double checkDistanceX=(mySizeX+targetSizeX+pEnemy->getActorData()->getAtackRangeX());
			double distanceX=pTarget->getX()-pEnemy->getX();
			
			int LowZ=static_cast<int>((pEnemy->getZ())-(0.8*(pEnemy->getActorData()->getAtackRangeZ())/2));
			int HighZ=static_cast<int>((pEnemy->getZ())+(0.8*(pEnemy->getActorData()->getAtackRangeZ())/2));
			int setLowZ=static_cast<int>(pTarget->getZ()-(targetSizeZ));
			int setHighZ=static_cast<int>(pTarget->getZ()+(targetSizeZ));

			bool checkZ=((LowZ<=setLowZ&&HighZ>=setLowZ)||(LowZ<=setHighZ&&HighZ>=setHighZ)||(setLowZ<=LowZ&&setHighZ>=HighZ));

			if(checkZ)
			{
				if((-checkDistanceX<distanceX&&distanceX<-targetSizeX)||(checkDistanceX>distanceX&&distanceX>targetSizeX))
				{
					r=true;			
				}
			}
		}
	}
	return r;
}