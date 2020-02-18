#pragma once
#include "Tile.h"
#include "ResourceManager.h"
class GameField : public sf::Drawable {
private:
	std::vector<std::vector<Tile>> tiles;
	sf::Sprite s;
public:
	GameField();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};