#include "Building.h"

Building::Building(BuildingType type, sf::Texture& texture)
	: GameEntity(texture), type(type)
{
	firstRound = true;
}

GangMembers Building::spawnGangMembers() {
	GangMembers gm(0);
	if (type == BuildingType::Dojo) {
		gm = GangMembers(2);
	}
	else if (type == BuildingType::SafeHouse) {
		if (this->firstRound) {
			gm = GangMembers(20);
			this->firstRound = false;
		}
		else {
			gm = GangMembers(4);
		}
	}
	gm.setPosition(getPosition());
	return gm;
}
