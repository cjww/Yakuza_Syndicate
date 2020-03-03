#include "PolicePatrol.h"

PolicePatrol::PolicePatrol() :GameEntity(*ResourceManager::getTexture("PolicePatrol"))
	,isPatrolling(true), inCustody(nullptr)
{
}

void PolicePatrol::move()
{

}
