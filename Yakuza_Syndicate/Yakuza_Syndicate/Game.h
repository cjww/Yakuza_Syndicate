#include "Player.h"

class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time timePerFrame;
	
	Player players[2];
	int turn;

public:
	Game();
	virtual ~Game();

	void handleEvents();
	void update();
	void draw();
};