#include "Territory.h"

void Territory::updateTerritory() {
	
	std::set<Tile*> safehouseTiles = gameField->getSurroundingTiles(gameField->getTileAt(safeHouse.getPosition()));
	tilesInTerritory.insert(safehouseTiles.begin(), safehouseTiles.end());

	for (int i = 0; i < dojos.size(); i++) {
		if (dojos[i]->getType() != BuildingType::DOJO_CONSTRUCTION) {
			std::set<Tile*> surroundingTiles = gameField->getSurroundingTiles(gameField->getTileAt(dojos[i]->getPosition()));
			tilesInTerritory.insert(surroundingTiles.begin(), surroundingTiles.end());
		}
	}

}

Territory::Territory(GameField* gameField, Owner owner)
	: safeHouse(BuildingType::SAFEHOUSE, ResourceManager::getTexture("SafeHouse")),
	gameField(gameField), owner(owner) {

	safeHouse.setOwner(owner);
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

Territory::~Territory() {
	for (auto& dojo : dojos) {
		delete dojo;
	}
}

int Territory::getIncome() {
	return tilesInTerritory.size() * 50;
}

std::vector<GangMembers*> Territory::getNewGangMembers() {
	std::vector<GangMembers*> allGangMembers;
	for (auto& dojo : dojos) {
		GangMembers* gm = dojo->spawnGangMembers();
		if (gm != nullptr) {
			allGangMembers.push_back(gm);
		}
		if (dojo->getType() == BuildingType::DOJO_CONSTRUCTION) {
			dojo->finishConstructing();
			updateTerritory();
		}
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
		Building* newDojo = new Building(BuildingType::DOJO_CONSTRUCTION, ResourceManager::getTexture("Dojo_Construct"));
		newDojo->setOwner(owner);
		newDojo->setPosition(tile->getPosition());
		dojos.push_back(newDojo);
		tile->setBuilding(dojos.back());
		updateTerritory();
	}
}

void Territory::removeDojo(Building* toRemove)
{

	//mutex->lock();
	bool removed = false;
	for (int i = 0; i < dojos.size() && !removed; i++)
	{
		if (toRemove == dojos[i])
		{
			delete dojos[i];
			dojos.erase(dojos.begin() + i);
			removed = true;
		}
	}
	//mutex->unlock();

}

void Territory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (const auto& tile : tilesInTerritory) {
		sf::RectangleShape rect(sf::Vector2f(tile->getGlobalBounds().width, tile->getGlobalBounds().height));
		rect.setPosition(tile->getPosition());
		sf::Color c = this->color;
		c.a = 100;
		rect.setFillColor(c);
		target.draw(rect);
	}

	for (const auto& dojo : dojos) {
		target.draw(*dojo, states);
	}

	target.draw(safeHouse, states);
}
