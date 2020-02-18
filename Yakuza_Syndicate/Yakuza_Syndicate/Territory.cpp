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

}

int Territory::getIncome() {
	return tilesInTerritory.size() * 50;
}

void Territory::setColor(sf::Color color) {
	this->color = color;
}

void Territory::buildDojo(sf::Vector2f position) {
	Tile* tile = gameField->getTileAt(position);
	Building newDojo(BuildingType::Dojo, *ResourceManager::getTexture("Dojo"));
	newDojo.setPosition(tile->getPosition());
	dojos.push_back(newDojo);

}

void Territory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& k : tilesInTerritory) {
		sf::RectangleShape rect(sf::Vector2f(k->getGlobalBounds().width, k->getGlobalBounds().height));
		rect.setPosition(k->getPosition());
		rect.setOutlineColor(this->color * sf::Color(200));
		rect.setFillColor(sf::Color::Transparent);
		target.draw(rect);
	}

	for (const auto& dojo : dojos) {
		target.draw(dojo);
	}

	target.draw(safeHouse);
}
