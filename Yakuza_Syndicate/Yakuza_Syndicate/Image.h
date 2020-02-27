#pragma once
#include "UIElement.h"

class Image : public UIElement {
private:
	sf::Sprite sprite;
public:
	Image(const sf::Texture& texture, const UIVisualSettings& visuals = {});
	Image(const sf::Texture& texture, sf::IntRect textureRect, const UIVisualSettings& visuals = {});
	
	virtual sf::Vector2f getPosition() const;
	virtual void setPosition(sf::Vector2f position);
	virtual sf::FloatRect getBounds() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
