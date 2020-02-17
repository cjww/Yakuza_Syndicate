#include "Player.h"
#include "GameField.h"
class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time timePerFrame;
	
	Player players[2];
	int turn;

	GameField gameField;

public:
	Game();
	virtual ~Game();

	void handleEvents();
	void update();
	void draw();
};