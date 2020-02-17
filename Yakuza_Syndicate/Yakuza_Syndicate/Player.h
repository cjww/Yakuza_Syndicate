#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
private:

public:
	Player();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};