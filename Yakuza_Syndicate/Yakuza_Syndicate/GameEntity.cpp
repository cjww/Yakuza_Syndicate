#include "GameEntity.h"

GameEntity::GameEntity()
{
	scale = 2;
	this->sprite.scale(scale, scale);
	owner = Owner::NEUTRAL;
}

GameEntity::GameEntity(sf::Texture &texture)
	: GameEntity()
{
	this->sprite.setTexture(texture);
}

GameEntity::GameEntity(sf::Texture& texture, sf::IntRect textureRect) 
	: GameEntity(texture) 
{
	this->sprite.setTextureRect(textureRect);
}

GameEntity::GameEntity(const GameEntity& other)
{
	this->sprite = other.sprite;
	this->scale = other.scale;
}

void GameEntity::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

sf::Vector2f GameEntity::getPosition() const
{
	return this->sprite.getPosition();
}

void GameEntity::setOwner(Owner owner)
{
	this->owner = owner;
}

Owner GameEntity::getOwner()
{
	return this->owner;
}

void GameEntity::move(sf::Vector2f offset) 
{
	this->sprite.move(offset);
}

sf::FloatRect GameEntity::getGlobalBounds() const{
	return this->sprite.getGlobalBounds();
}

void GameEntity::flipSprite()
{
	sprite.setScale(-scale, scale);
	sprite.setOrigin(sprite.getLocalBounds().width, 0);
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}
