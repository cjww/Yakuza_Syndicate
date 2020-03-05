#include "GameField.h"

GameField::GameField(const sf::RenderWindow& window) {
	int scale = 2;
	fieldSize = 15;
	sf::Texture* tileTexture = ResourceManager::getTexture("Tiles");
	//sf::Vector2f offset = window.getSize() / 2.0f - sf::Vector2f(tileSize * scale * fieldSize / 2, 0);
	sf::Vector2f offset = sf::Vector2f(window.getSize().x / 4.0f, 0);

	for (int row = 0; row < fieldSize; row++) {
		for (int col = 0; col < fieldSize; col++) {
			tiles[row][col] = new Tile(*tileTexture, sf::IntRect(0, 0, Tile::size, Tile::size));
			tiles[row][col]->setPosition(offset + sf::Vector2f(col, row) * (float)Tile::size * 2.0f);
		}
	}
	policeStation.setScale(2, 2);
	policeStation.setTexture(*ResourceManager::getTexture("PoliceStation"));
	policeStation.setPosition(getTileByIndex(0, 0)->getPosition());

	bank.setScale(2, 2);
	bank.setTexture(*ResourceManager::getTexture("Bank"));
	bank.setPosition(getTileByIndex(14, 14)->getPosition());

	police.setPosition(getTileByIndex(0, 0)->getPosition());
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
	target.draw(policeStation);
	target.draw(bank);
	target.draw(police);
}

void GameField::movePolice()
{
	this->police.move(sf::Vector2f((int)police.getDirection() * 64, (int)police.getDirection() * 64));
	if (police.getPosition() == tiles[14][14]->getPosition())
	{
		police.changeDirection(Direction::STATION);
	}
	else if (police.getPosition() == tiles[0][0]->getPosition())
	{
		police.changeDirection(Direction::BANK);
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

Tile* GameField::getTileByIndex(int column, int row) const {
	Tile* tile = nullptr;
	if (row < 15 && row >= 0 && column < 15 && column >= 0) {
		tile = tiles[row][column];
	}
	return tile;
}
