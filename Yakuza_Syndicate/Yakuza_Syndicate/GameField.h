#pragma once
#include "Tile.h"
#include "ResourceManager.h"
#include "PolicePatrol.h"
#include "Bank.h"

#include <set>

class GameField : public sf::Drawable {
private:
	Tile* tiles[15][15];
	int fieldSize;
	Bank bank;
	PolicePatrol police;
	sf::Sprite policeStation;


public:
	GameField(const sf::RenderWindow& window);
	virtual ~GameField();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::set<Tile*> getSurroundingTiles(Tile* tile);

	void makeHeist(GangMembers* heistGM);
	void movePolice();
	Tile* getTileAt(sf::Vector2f pos) const;
	Tile* getTileByIndex(int column, int row) const;
	float lengthOfVector(sf::Vector2f vec);
};