#pragma once
#include "GameEntity.h"
#include "Tile.h"

class GangMembers : public GameEntity {
private:
	sf::Text text;
	sf::Font font;

	int amount;
	bool inBuilding;
	bool inFriendlyTerr;

public:
	GangMembers(int amount);
	
	bool merge(GangMembers& other);

	int getAmount();
	void move(Tile* moveTo);
	void fight(GangMembers &other);
};