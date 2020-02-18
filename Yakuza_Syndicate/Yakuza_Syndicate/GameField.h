#pragma once
#include "Tile.h"
#include "ResourceManager.h"
class GameField : public sf::Drawable {
private:
	Tile tiles[15][15];
	sf::Sprite s;
public:
	GameField(const sf::RenderWindow& window);
	virtual ~GameField();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};