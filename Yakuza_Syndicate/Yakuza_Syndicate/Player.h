#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Territory.h"
#include "GangMembers.h"

class Player : public sf::Drawable {
private:
	bool endTurn;
	sf::Color color;
	sf::Shader shader;

	//TODO add gangMember array
	std::vector<GangMembers> gangMembers;

	Territory territory;
	GameField* gameField;

	int balance;
		
public:
	Player(GameField* gameField);

	void mousePressed(sf::Vector2i mousePosition, sf::Mouse::Button button);

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getEndTurn() const;
	void setEndTurn(bool value);

	void setColor(sf::Color color);
};