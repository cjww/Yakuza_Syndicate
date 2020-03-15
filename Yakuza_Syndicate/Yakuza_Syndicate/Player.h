#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Mutex.hpp>

#include <iostream>
#include "Territory.h"
#include "GangMembers.h"
#include "UI.h"
#include "NetworkManager.h"


class Player : public sf::Drawable {
private:
	bool endTurn;
	sf::Color color;
	sf::Shader shader;

	Owner playernr;

	std::vector<GangMembers*> gangMembers;

	Territory territory;
	GameField* gameField;

	int income;
	int balance;
	int upkeep;
	int totalGM;
	
	sf::RectangleShape selectedTileRect;
	Tile* selectedTile;
	GangMembers* selectedGM;
	Label* selectedGmLabel;
	int selectedGmAmount;
	
	UIVisualSettings uiActiveVis;
	UIVisualSettings uiInactiveVis;

	Pane uiPane;
	Button* endTurnBtn;
	bool canBuildDojo;
	Button* buildDojoBtn;
	bool canMakeHeist;
	Button* makeHeistBtn;
	Label* balanceLabel;
	Label* incomeLabel;
	Label* totalGmLabel;
	Label* gmUpkeepLabel;

	sf::RenderWindow& window;

	sf::Sound katanaSound;
	sf::Sound hammerSound;
	sf::Sound coinSound;

	sf::Mutex* mutex;

public:
	Player(GameField* gameField, Owner owner, sf::RenderWindow& window);
	Player(const Player& otherPlayer);
	virtual ~Player();

	void checkFight(Player* other);
	void removeGM(GangMembers* toRemove);
	void updateUpkeep();
	void updateTotalGM();

	GangMembers* getGMAtPos(sf::Vector2f pos);
	void mousePressed(sf::Vector2f mousePosition, sf::Mouse::Button button);
	void keyPressed(sf::Keyboard::Key key);

	void update();
	void drawTerritory(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool wantsToEndTurn() const;
	
	void turnEnd();
	void turnStart();

	void setColor(sf::Color color);
	sf::Color getColor();

	bool checkIfWin();

	void proccessMessage(Message& msg);

	void buildDojo(GangMembers* gm);
	void makeHeist(GangMembers* gm);

	bool selectTile(Tile* tile);
	GangMembers* trySplitGM(GangMembers* gm, int amount);
	bool moveGM(GangMembers* gmToMove, int amount, Tile* toTile);


};