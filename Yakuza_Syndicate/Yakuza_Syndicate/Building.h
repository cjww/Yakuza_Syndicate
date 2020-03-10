#pragma once
#include "GameEntity.h"
#include "GangMembers.h"

enum class BuildingType { DOJO, SAFEHOUSE };

class Building : public GameEntity {
private:
	BuildingType type;
	bool firstRound;
public:
	Building(BuildingType type, sf::Texture& texture);

	GangMembers* spawnGangMembers();
};
