#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "actor.h"

class Player:public Actor
{
private:
	

public :

	Player();
	virtual ~Player();	

	void move(Input* pInput,listSpActor* plspActors);

	void update(Input* pInput,listSpActor* plspActors);

	void reset();
};




#endif
