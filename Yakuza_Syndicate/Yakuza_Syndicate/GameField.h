#pragma once
#include "Tile.h"

class GameField : public sf::Drawable {
private:
	std::vector<std::vector<Tile>> tiles;

public:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};