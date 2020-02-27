#pragma once

#include "UIElement.h"

class Pane : public UIElement {
private:
	sf::RectangleShape shape;

public:
	Pane(const UIVisualSettings& visuals = {});
	Pane(sf::Vector2f size, const UIVisualSettings& visuals = {});

	virtual void setPosition(sf::Vector2f position);
	virtual sf::Vector2f getPosition() const;
	virtual sf::FloatRect getBounds() const;

	void setSize(sf::Vector2f size);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};