#include "GameField.h"

GameField::GameField(const sf::RenderWindow& window) {
	int scale = 2;
	fieldSize = 15;
	sf::Texture* tileTexture = &ResourceManager::getTexture("Tiles");
	//sf::Vector2f offset = window.getSize() / 2.0f - sf::Vector2f(tileSize * scale * fieldSize / 2, 0);
	sf::Vector2f offset = sf::Vector2f(window.getSize().x / 4.0f, 0);


	for (int row = 0; row < fieldSize; row++) {
		for (int col = 0; col < fieldSize; col++) {
			tiles[row][col] = new Tile(*tileTexture, sf::IntRect(0, 0, Tile::size, Tile::size));
			tiles[row][col]->setPosition(offset + sf::Vector2f(col, row) * (float)Tile::size * 2.0f);
		}
	}
	policeStation.setScale(2, 2);
	policeStation.setTexture(ResourceManager::getTexture("PoliceStation"));
	policeStation.setPosition(getTileByIndex(0, 0)->getPosition());

	bank.setPosition(getTileByIndex(14, 14)->getPosition());

	police.setPosition(getTileByIndex(0, 0)->getPosition());

	policeRectShape.setPosition(police.getPosition() - sf::Vector2f(64, 64));
	policeRectShape.setFillColor(sf::Color::Transparent);
	policeRectShape.setOutlineThickness(1);
	policeRectShape.setSize(sf::Vector2f(64 * 3, 64 * 3));
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
	target.draw(policeRectShape);
}

std::set<Tile*> GameField::getSurroundingTiles(Tile* tile)
{
	std::set<Tile*> surroundingTiles;
	sf::Vector2f tilePos = tile->getPosition();
	
	surroundingTiles.insert(tile);
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(64, 0)));
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(-64, 0)));
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(0, 64)));
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(0, -64)));
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(64, 64)));
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(64, -64)));
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(-64, 64)));
	surroundingTiles.insert(getTileAt(tilePos + sf::Vector2f(-64, -64)));

	if (surroundingTiles.find(nullptr) != surroundingTiles.end()) {
		surroundingTiles.erase(nullptr);
	}

	return surroundingTiles;
}

void GameField::makeHeist(GangMembers* heistGM)
{
	heistGM->setAmount(heistGM->getAmount() - bank.heist());
}

void GameField::movePolice()
{
	this->police.move(sf::Vector2f((int)police.getDirection() * 64, (int)police.getDirection() * 64));
	policeRectShape.setPosition(police.getPosition() - sf::Vector2f(64, 64));
	if (police.getPosition() == tiles[14][14]->getPosition())
	{
		police.changeDirection(Direction::STATION);
	}
	else if (police.getPosition() == tiles[0][0]->getPosition())
	{
		police.changeDirection(Direction::BANK);
	}
	std::set<Tile*> tiles = getSurroundingTiles(getTileAt(police.getPosition()));
	for (Tile* tile : tiles)
	{
		if (tile->getGangMembers() != nullptr)
		{
			tile->getGangMembers()->setAmount(0);
			tile->setGangMembers(nullptr);
			police.changeDirection(Direction::STATION);
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

Tile* GameField::getTileByIndex(int column, int row) const {
	Tile* tile = nullptr;
	if (row < 15 && row >= 0 && column < 15 && column >= 0) {
		tile = tiles[row][column];
	}
	return tile;
}

float GameField::lengthOfVector(sf::Vector2f vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

void GameField::updateAnimations() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			GangMembers* gm = tiles[i][j]->getGangMembers();
			if (gm != nullptr) {
				gm->update();
			}
		}
	}
}
