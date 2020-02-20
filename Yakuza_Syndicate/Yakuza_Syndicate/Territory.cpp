#include "Territory.h"

void Territory::updateTerritory() {
	
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

}

Territory::Territory(GameField* gameField)
	: safeHouse(BuildingType::SafeHouse, *ResourceManager::getTexture("SafeHouse")),
	gameField(gameField) {

	Tile* bottomLeft = gameField->getTileByIndex(0, 14);
	if (bottomLeft->getBuilding() == nullptr) {
		safeHouse.setPosition(bottomLeft->getPosition());
		bottomLeft->setBuilding(&safeHouse);
	}
	else {
		Tile* topRight = gameField->getTileByIndex(14, 0);
		safeHouse.setPosition(topRight->getPosition());
		topRight->setBuilding(&safeHouse);
	}
	
	updateTerritory();
}

int Territory::getIncome() {
	return tilesInTerritory.size() * 50;
}

void Territory::setColor(sf::Color color) {
	this->color = color;
}

void Territory::buildDojo(sf::Vector2f position) {
	Tile* tile = gameField->getTileAt(position);
	if (tile->getBuilding() == nullptr) {
		Building newDojo(BuildingType::Dojo, *ResourceManager::getTexture("Dojo"));
		newDojo.setPosition(tile->getPosition());
		dojos.push_back(newDojo);
		tile->setBuilding(&dojos.back());
		updateTerritory();
	}
}

void Territory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& k : tilesInTerritory) {
		sf::RectangleShape rect(sf::Vector2f(k->getGlobalBounds().width, k->getGlobalBounds().height));
		rect.setPosition(k->getPosition());
		sf::Color c = this->color;
		c.a = 40;
		rect.setOutlineColor(this->color);
		rect.setOutlineThickness(1);
		//rect.setFillColor(sf::Color::Transparent);
		rect.setFillColor(c);
		target.draw(rect);
	}

	for (const auto& dojo : dojos) {
		target.draw(dojo, states);
	}

	target.draw(safeHouse, states);
}
