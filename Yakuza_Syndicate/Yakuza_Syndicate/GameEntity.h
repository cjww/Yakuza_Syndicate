#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

enum class Owner {PLAYER1, PLAYER2, NEUTRAL};

class GameEntity : public sf::Drawable {
private:
	sf::Sprite sprite;
	Owner owner;

	int scale;

	float animTimer;
	int animFrame;
	sf::IntRect animRect;
public:
	GameEntity();
	GameEntity(sf::Texture &texture);
	GameEntity(sf::Texture &texture, sf::IntRect textureRect);
	GameEntity(const GameEntity& other);

	virtual void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
	void setOwner(Owner owner);
	Owner getOwner();
	
	void move(sf::Vector2f offset);

	sf::FloatRect getGlobalBounds() const;

	void flipSprite();

	void setTexture(sf::Texture& texture);
	void setTexture(sf::Texture& texture, sf::IntRect textureRect);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//void setupAnimation(sf::Texture& texture, int imageSize, int length, float speed);
	void animate(sf::Texture* tex, int imageSize, int length, float speed);
};