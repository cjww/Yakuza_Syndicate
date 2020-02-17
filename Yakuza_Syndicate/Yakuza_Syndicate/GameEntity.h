#pragma once
#include <SFML/Graphics.hpp>

class GameEntity : public sf::Drawable {
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	GameEntity(sf::Texture &texture);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};