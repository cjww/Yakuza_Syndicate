#include "GameField.h"

GameField::GameField(const sf::RenderWindow& window) {
	sf::Texture* tileTexture = ResourceManager::newTexture("../res/tiles.png", "Tiles");
	int tileSize = 32;
	int scale = 2;
	int fieldSize = 15;

	//sf::Vector2f offset = window.getSize() / 2.0f - sf::Vector2f(tileSize * scale * fieldSize / 2, 0);
	sf::Vector2f offset = sf::Vector2f(window.getSize().x / 4.0f, 0);

	for (int row = 0; row < fieldSize; row++) {
		for (int col = 0; col < fieldSize; col++) {
			tiles[row][col] = Tile(*tileTexture, sf::IntRect(0, 0, tileSize, tileSize));
			tiles[row][col].setPosition(offset + sf::Vector2f(col, row) * (float)tileSize * 2.0f);
		}
	}
}

GameField::~GameField() {

}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			target.draw(tile);
		}
	}
}
