#include "Player.h"
#include "GameField.h"

#include "UI.h"
class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time timePerFrame;
	
	GameField gameField;
	
	Player players[2];
	int turnIndex;

	Pane elem;

public:
	Game();
	virtual ~Game();

	void handleEvents();
	void update();
	void draw();
};