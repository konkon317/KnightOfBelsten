#ifndef INCLUDE_AI_H
#define INCLUDE_AI_H

#include "../../defines.h"
#include "../actor/enemy.h"

struct AiData
{
	double moveX;
	double moveY;
	
	bool atackStartFlag;

	AiData()
	{
		moveX=0.0;
		moveY=0.0;
		atackStartFlag=false;
	}
};

extern AiData think( Enemy * pEnemy,const sp_Actor spPlayer,const listSpActor& pLSpActors);


#endif