#pragma once
#include "Building.h"

class Territory : public sf::Drawable{
private:
	std::vector<Building> dojos;
	Building safeHouse;

public:
	Territory();

	int getIncome();


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};