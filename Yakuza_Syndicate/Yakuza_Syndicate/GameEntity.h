#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class GameEntity : public sf::Drawable {
private:
	sf::Sprite sprite;

	int scale;
public:
	GameEntity();
	GameEntity(sf::Texture &texture);
	GameEntity(sf::Texture &texture, sf::IntRect textureRect);
	GameEntity(const GameEntity& other);

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
	
	void move(sf::Vector2f offset);

	sf::FloatRect getGlobalBounds() const;

	void flipSprite();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};