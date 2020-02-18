#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Territory.h"

class Player : public sf::Drawable {
private:
	bool endTurn;
	sf::Color color;

	//TODO add gangMember array
	
	Territory territory;

	int balance;
		
public:
	Player(GameField* gameField);

	void mousePressed(sf::Vector2i mousePosition);

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getEndTurn() const;
	void setEndTurn(bool value);

	void setColor(sf::Color color);
};