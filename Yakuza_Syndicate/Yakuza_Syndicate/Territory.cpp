#include "Territory.h"

void Territory::updateTerritory() {
	
	for (int i = 0; i <= dojos.size(); i++) {
		sf::Vector2f bPos = safeHouse.getPosition();
		if (i < dojos.size()) {
			bPos = dojos[i].getPosition();
		}

		
		std::set<Tile*> surroundingTiles = gameField->getSurroundingTiles(gameField->getTileAt(bPos));
		tilesInTerritory.insert(surroundingTiles.begin(), surroundingTiles.end());
	}


}

Territory::Territory(GameField* gameField)
	: safeHouse(BuildingType::SAFEHOUSE, *ResourceManager::getTexture("SafeHouse")),
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

std::vector<GangMembers> Territory::getNewGangMembers() {
	std::vector<GangMembers> allGangMembers;
	for (auto& dojo : dojos) {
		GangMembers gm = dojo.spawnGangMembers();
		allGangMembers.push_back(gm);
	}

	allGangMembers.push_back(safeHouse.spawnGangMembers());

	return allGangMembers;
}

bool Territory::checkIfTileInTerr(Tile* tile)
{
	bool found = false;
	if (tilesInTerritory.find(tile) != tilesInTerritory.end())
	{
		found = true;
	}
	return found;
}

void Territory::setColor(sf::Color color) {
	this->color = color;
}

void Territory::buildDojo(sf::Vector2f position) {
	Tile* tile = gameField->getTileAt(position);
	if (tile != nullptr && tile->getBuilding() == nullptr) {
		Building newDojo(BuildingType::DOJO, *ResourceManager::getTexture("Dojo"));
		newDojo.setPosition(tile->getPosition());
		dojos.push_back(newDojo);
		tile->setBuilding(&dojos.back());
		updateTerritory();
	}
}

void Territory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (const auto& tile : tilesInTerritory) {
		sf::RectangleShape rect(sf::Vector2f(tile->getGlobalBounds().width, tile->getGlobalBounds().height));
		rect.setPosition(tile->getPosition());
		sf::Color c = this->color;
		c.a = 100;
		//rect.setFillColor(sf::Color::Transparent);
		rect.setFillColor(c);
		target.draw(rect);
	}

	for (const auto& dojo : dojos) {
		target.draw(dojo, states);
	}

	target.draw(safeHouse, states);
}
