#include "GameEntity.h"

GameEntity::GameEntity()
{
}

void GameEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw->(this->sprite);
}
