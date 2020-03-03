#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Territory.h"
#include "GangMembers.h"
#include "UI.h"

class Player : public sf::Drawable {
private:
	bool endTurn;
	sf::Color color;
	sf::Shader shader;

	Owner playernr;

	std::vector<GangMembers> gangMembers;

	Territory territory;
	GameField* gameField;

	int balance;
	sf::RectangleShape selectedTileRect;
	Tile* selectedTile;
	GangMembers* selectedGM;
	
	UIVisualSettings uiActiveVis;
	UIVisualSettings uiInactiveVis;

	Pane uiPane;
	Button* endTurnBtn;
	bool canBuildDojo;
	Button* buildDojoBtn;
	Label* balanceLabel;
	Label* incomeLabel;
	Label* totalGmLabel;

	sf::RenderWindow& window;

public:
	Player(GameField* gameField, Owner owner, sf::RenderWindow& window);
	Player(const Player& otherPlayer);

	GangMembers* getGMAtPos(sf::Vector2f pos);
	void mousePressed(sf::Vector2f mousePosition, sf::Mouse::Button button);

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool wantsToEndTurn() const;
	
	void turnEnd();
	void turnStart();

	void setColor(sf::Color color);
};