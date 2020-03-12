#include "PolicePatrol.h"

PolicePatrol::PolicePatrol() :GameEntity(ResourceManager::getTexture("PolicePatrol"))
	,direction(Direction::BANK)
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

