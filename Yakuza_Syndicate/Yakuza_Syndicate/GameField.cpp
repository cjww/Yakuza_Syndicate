#include "GameField.h"

GameField::GameField(){
	
}

void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto row : tiles) {
		for (auto tile : row) {
			target.draw(tile);
		}
	}
}
