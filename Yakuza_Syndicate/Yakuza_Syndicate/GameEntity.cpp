#include "GameEntity.h"

GameEntity::GameEntity()
{
}

GameEntity::GameEntity(sf::Texture &texture)
	:texture(texture)
{
	this->sprite.setTexture(texture);
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
