#pragma once
#include "Building.h"
#include "GameField.h"
#include <set>

class Territory : public sf::Drawable{
private:
	std::vector<Building> dojos;
	Building safeHouse;
	sf::Color color;
	GameField* gameField;

	std::set<Tile*> tilesInTerritory;
	void updateTerritory();

public:
	Territory(GameField* gameField);


	int getIncome();
	std::vector<GangMembers*> getNewGangMembers();
	bool checkIfTileInTerr(Tile* tile);

	void setColor(sf::Color color);

	void buildDojo(sf::Vector2f position);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};