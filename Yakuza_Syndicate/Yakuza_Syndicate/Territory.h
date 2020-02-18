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

	std::set<Tile*> calcTerritory();

public:
	Territory(GameField* gameField);

	int getIncome();

	void setColor(sf::Color color);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};