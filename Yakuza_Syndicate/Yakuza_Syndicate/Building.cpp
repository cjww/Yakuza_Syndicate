#include "Building.h"

Building::Building(BuildingType type, sf::Texture& texture)
	: GameEntity(texture), type(type)
{
	firstRound = true;
}

GangMembers Building::spawnGangMembers() {
	GangMembers gm(0);
	if (type == BuildingType::DOJO) {
		gm = GangMembers(2);
	}
	else if (type == BuildingType::SAFEHOUSE) {
		if (this->firstRound) {
			gm = GangMembers(20);
			this->firstRound = false;
		}
		else {
			gm = GangMembers(4);
		}
	}
	gm.setPosition(getPosition());
	gm.setTextPos(getPosition());
	return gm;
}
