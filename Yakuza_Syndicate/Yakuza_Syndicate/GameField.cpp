#include "GameField.h"

GameField::GameField(const sf::RenderWindow& window) {
	ResourceManager::newTexture("../res/Dojo.png", "Dojo");
	ResourceManager::newTexture("../res/Safe-House.png", "SafeHouse");

	sf::Texture* tileTexture = ResourceManager::newTexture("../res/tiles.png", "Tiles");
	int scale = 2;
	tileSize = 32;
	fieldSize = 15;
	//sf::Vector2f offset = window.getSize() / 2.0f - sf::Vector2f(tileSize * scale * fieldSize / 2, 0);
	sf::Vector2f offset = sf::Vector2f(window.getSize().x / 4.0f, 0);

	for (int row = 0; row < fieldSize; row++) {
		for (int col = 0; col < fieldSize; col++) {
			tiles[row][col] = new Tile(*tileTexture, sf::IntRect(0, 0, tileSize, tileSize));
			tiles[row][col]->setPosition(offset + sf::Vector2f(col, row) * (float)tileSize * 2.0f);
		}
	}
}

GameField::~GameField() {
	for (auto& row : tiles) {
		for (auto& tile : row) {
			delete tile;
		}
	}
}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			target.draw(*tile);
		}
	}
}

Tile* GameField::getTileAt(sf::Vector2f pos) const {
	Tile* tileAt = nullptr;
	for (int i = 0; i < fieldSize && tileAt == nullptr; i++) {
		for (int j = 0; j < fieldSize && tileAt == nullptr; j++) {
			if (tiles[i][j]->getGlobalBounds().contains(pos)) {
				tileAt = tiles[i][j];
			}
		}
	}
	return tileAt;
}

Tile* GameField::getTileByIndex(int row, int column) const {
	Tile* tile = nullptr;
	if (row < 15 && row >= 0 && column < 15 && column >= 0) {
		tile = tiles[row][column];
	}
	return tile;
}
