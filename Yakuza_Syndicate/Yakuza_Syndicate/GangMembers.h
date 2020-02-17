#pragma once
#include "GameEntity.h"

class GangMembers : public GameEntity {
private:
	int amount;
	bool inBuilding;
	bool inFriendlyTerr;

public:
	GangMembers();

	void move();
	void fight(GangMembers &other);
};