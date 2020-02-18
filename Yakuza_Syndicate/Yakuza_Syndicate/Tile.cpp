#include "Tile.h"

Tile::Tile() : building(nullptr) {

}

Tile::Tile(sf::Texture& texture, sf::IntRect textureRect) : GameEntity(texture, textureRect) {
	building = nullptr;
}

Building* Tile::getBuilding() const {
	return building;
}

void Tile::setBuilding(Building* building) {
	this->building = building;
}
