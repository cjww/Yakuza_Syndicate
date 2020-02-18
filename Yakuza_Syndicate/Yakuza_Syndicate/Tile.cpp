#include "Tile.h"

Tile::Tile() : building(nullptr){

}

Tile::Tile(sf::Texture& texture, sf::IntRect textureRect) : GameEntity(texture, textureRect) {
	
}
