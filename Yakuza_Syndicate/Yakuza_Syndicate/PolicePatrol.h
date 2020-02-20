#pragma once
#include "GameEntity.h"
#include "GangMembers.h"

class PolicePatrol : public GameEntity {
private:
	bool isPatrolling;
	GangMembers* inCustody;

public:
	PolicePatrol();


	void move();
};