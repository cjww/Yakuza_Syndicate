#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Building.h"

class Tile : public GameEntity {
private:
	Building* building;
public:
	Tile();
	Tile(sf::Texture& texture, sf::IntRect textureRect);

	Building* getBuilding() const;
	void setBuilding(Building* building);

};