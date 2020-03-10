#include "Tile.h"

Tile::Tile() : building(nullptr) {

}

Tile::Tile(sf::Texture& texture, sf::IntRect textureRect) : GameEntity(texture, textureRect) {
	building = nullptr;
	gangMembers = nullptr;
}

Building* Tile::getBuilding() const {
	return building;
}

void Tile::setBuilding(Building* building) {
	this->building = building;
}

GangMembers* Tile::getGangMembers() const
{
	return gangMembers;
}

void Tile::setGangMembers(GangMembers* gangMembers)
{
	this->gangMembers = gangMembers;
}
