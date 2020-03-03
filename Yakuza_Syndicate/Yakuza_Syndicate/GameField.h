#pragma once
#include "Tile.h"
#include "ResourceManager.h"
#include "PolicePatrol.h"

class GameField : public sf::Drawable {
private:
	Tile* tiles[15][15];
	int fieldSize;
	PolicePatrol police;

	sf::Sprite policeStation;
	sf::Sprite bank;

public:
	GameField(const sf::RenderWindow& window);
	virtual ~GameField();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Tile* getTileAt(sf::Vector2f pos) const;
	Tile* getTileByIndex(int column, int row) const;

};