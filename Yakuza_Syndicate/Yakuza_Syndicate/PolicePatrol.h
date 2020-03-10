#pragma once
#include "GameEntity.h"
#include "GangMembers.h"

enum class Direction {BANK = 1, STATION = -1};

class PolicePatrol : public GameEntity {
private:
	Direction direction;

public:
	PolicePatrol();

	Direction getDirection();
	void changeDirection(Direction direction);
};