#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Building.h"

class Tile : public GameEntity {
private:
	Building* building;
public:
	Tile();
};