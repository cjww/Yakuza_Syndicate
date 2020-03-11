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
	else if(type == BuildingType::DOJO){
		gm = new GangMembers(2);
	}
	if (gm != nullptr) {
		gm->setPosition(getPosition());
	}
	return gm;
}

void Building::finishConstructing() {
	if (type == BuildingType::DOJO_CONSTRUCTION) {
		type = BuildingType::DOJO;
		setTexture(*ResourceManager::getTexture("Dojo"));
	}

}

BuildingType Building::getType() const {
	return type;
}
