#pragma once
#include "GameEntity.h"

class GangMembers : public GameEntity {
private:
	sf::Text text;
	sf::Font font;

	int amount;
	bool inBuilding;
	bool inFriendlyTerr;

public:
	GangMembers(int amount);

	void move();
	void fight(GangMembers &other);
};