#include "Building.h"

Building::Building(BuildingType type, sf::Texture& texture)
	: GameEntity(texture), type(type)
{
	firstRound = true;
}

GangMembers* Building::spawnGangMembers() {
	GangMembers* gm = nullptr;
	if (type == BuildingType::SAFEHOUSE) {
		if (this->firstRound) {
			gm = new GangMembers(20);
			this->firstRound = false;
		}
		else {
			gm = new GangMembers(4);
		}
	}
	else {
		gm = new GangMembers(2);
	}
	gm->setPosition(getPosition());
	return gm;
}
