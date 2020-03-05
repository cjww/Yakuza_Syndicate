#include "PolicePatrol.h"

PolicePatrol::PolicePatrol() :GameEntity(*ResourceManager::getTexture("PolicePatrol"))
	,direction(Direction::BANK), inCustody(nullptr)
{
}

Direction PolicePatrol::getDirection()
{
	return direction;
}

void PolicePatrol::changeDirection(Direction direction)
{
	this->direction = direction;
}
