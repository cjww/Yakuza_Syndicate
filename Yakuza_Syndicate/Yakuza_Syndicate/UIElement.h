#pragma once
#include <vector>
#include "GameEntity.h"
class UIElement : public GameEntity {
private:
	std::vector<UIElement*> children;
	UIElement* parent;
	
public:
	UIElement();
	UIElement(sf::Texture& texture);
	virtual ~UIElement();
	
	UIElement* addChild(UIElement* elem);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};