#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class GameEntity : public sf::Drawable {
private:
	sf::Sprite sprite;
public:
	GameEntity();
	GameEntity(sf::Texture &texture);
	GameEntity(sf::Texture &texture, sf::IntRect textureRect);

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
	
	void move(sf::Vector2f offset);

	sf::FloatRect getGlobalBounds() const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};