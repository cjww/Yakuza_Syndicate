#include "GameField.h"

GameField::GameField(){
	sf::Texture* tileTexture = ResourceManager::newTexture("../res/tiles.png", "tiles");
	for (auto& row : tiles) {
		for (auto& tile : row) {
			tile = Tile(*tileTexture);
		}
	}
}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			target.draw(tile);
		}
	}
}
