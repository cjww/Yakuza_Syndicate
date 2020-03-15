#pragma once
#include "Building.h"
#include "GameField.h"
#include <set>
#include <SFML/System/Mutex.hpp>

class Territory : public sf::Drawable{
private:
	std::vector<Building*> dojos;
	Building safeHouse;
	sf::Color color;
	GameField* gameField;
	Owner owner;

	std::set<Tile*> tilesInTerritory;

	sf::Mutex* mutex;
	void updateTerritory();

public:
	Territory(GameField* gameField, Owner owner);
	virtual ~Territory();

	int getIncome();
	std::vector<GangMembers*> getNewGangMembers();
	bool checkIfTileInTerr(Tile* tile);

	void setColor(sf::Color color);

	void buildDojo(sf::Vector2f position);
	void removeDojo(Building* toRemove);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};