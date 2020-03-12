#include "Bank.h"

Bank::Bank()
	:GameEntity(ResourceManager::getTexture("Bank")),
	security(0)
{
}

int Bank::heist()
{
	security += 2;
	return security;
}
