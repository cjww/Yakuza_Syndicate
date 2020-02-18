#include "Building.h"

Building::Building(BuildingType type, sf::Texture& texture)
	: GameEntity(texture), type(type)
{
}
