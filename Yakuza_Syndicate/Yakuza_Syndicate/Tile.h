#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "Building.h"
#include "GangMembers.h"

class Tile : public GameEntity {
private:
	Building* building;
	GangMembers* gangMembers;
public:
	Tile();
	Tile(sf::Texture& texture, sf::IntRect textureRect);

	static const int size = 32;

	Building* getBuilding() const;
	void setBuilding(Building* building);

	GangMembers* getGangMembers() const;
	void setGangMembers(GangMembers* gangMembers);

};