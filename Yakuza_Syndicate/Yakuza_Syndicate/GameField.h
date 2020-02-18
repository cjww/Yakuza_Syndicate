#pragma once
#include "Tile.h"
#include "ResourceManager.h"
class GameField : public sf::Drawable {
private:
	Tile* tiles[15][15];
	int tileSize;
	int fieldSize;
public:
	GameField(const sf::RenderWindow& window);
	virtual ~GameField();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Tile* getTileAt(sf::Vector2f pos) const;
	Tile* getTileByIndex(int column, int row) const;

};