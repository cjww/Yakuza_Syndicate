#include "Territory.h"

std::set<Tile*> Territory::calcTerritory() {
	std::set<Tile*> tilesInTerritory;

	for (int i = 0; i <= dojos.size(); i++) {
		sf::Vector2f bPos = safeHouse.getPosition();
		if (i < dojos.size()) {
			bPos = dojos[i].getPosition();
		}

		tilesInTerritory.insert(gameField->getTileAt(bPos));
		
		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(64, 0)));
		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(-64, 0)));
		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(0, 64)));
		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(0, -64)));

		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(64, 64)));
		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(64, -64)));
		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(-64, 64)));
		tilesInTerritory.insert(gameField->getTileAt(bPos + sf::Vector2f(-64, -64)));
	}
	
	if (tilesInTerritory.find(nullptr) != tilesInTerritory.end()) {
		tilesInTerritory.erase(nullptr);
	}

	return tilesInTerritory;
}

Territory::Territory(GameField* gameField)
	: safeHouse(BuildingType::SafeHouse),
	gameField(gameField) {

}

int Territory::getIncome() {
	return calcTerritory().size() * 50;
}

void Territory::setColor(sf::Color color) {
	this->color = color;
}

void Territory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
