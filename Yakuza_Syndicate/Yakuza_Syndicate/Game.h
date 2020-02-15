#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	virtual ~Game();

	void handleEvents();
	void update();
	void draw();

private:
	sf::RenderWindow m_window;
	sf::Clock m_clock;

};