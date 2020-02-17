#pragma once
#include "GameEntity.h"

enum class BuildingType { Dojo, SafeHouse };

class Building : public GameEntity {
private:
	BuildingType type;

public:
	Building(BuildingType type);
};
