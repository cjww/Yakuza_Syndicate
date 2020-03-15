#include "GameEntity.h"

GameEntity::GameEntity()
{
	scale = 2;
	this->sprite.scale(scale, scale);
	owner = Owner::NEUTRAL;

	animFrame = 0;
	animTimer = 0.f;
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

void GameEntity::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture, true);
}

void GameEntity::setTexture(sf::Texture& texture, sf::IntRect textureRect) {
	sprite.setTexture(texture);
	sprite.setTextureRect(textureRect);
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}

void GameEntity::animate(sf::Texture* tex, int imageSize, int length, float timePerFrame) {
	sprite.setTexture(*tex);
	sf::IntRect animRect(animFrame * imageSize, 0, imageSize, imageSize);
	sprite.setTextureRect(animRect);
	animTimer++;
	if (animTimer >= timePerFrame * 60.f) {
		animTimer = 0;
		animFrame = (animFrame + 1) % length;
	}
}
