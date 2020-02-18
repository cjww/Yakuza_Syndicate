#include "GameEntity.h"

GameEntity::GameEntity()
{
	this->sprite.scale(2, 2);
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

void GameEntity::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

sf::Vector2f GameEntity::getPosition()
{
	return this->sprite.getPosition();
}

void GameEntity::move(sf::Vector2f offset) 
{
	this->sprite.move(offset);
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
