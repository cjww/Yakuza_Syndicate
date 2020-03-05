#pragma once
#include "UIElement.h"
class Label : public UIElement {
private:
	sf::Font font;
	sf::Text text;

	sf::CircleShape c;
public:
	Label(std::string str, const UIVisualSettings& visuals = {});

	virtual sf::Vector2f getPosition() const;
	virtual void setPosition(sf::Vector2f position);

	void setString(const std::string& string);
	std::string getString() const;

	virtual sf::FloatRect getBounds() const;

	virtual void setVisuals(const UIVisualSettings& visuals);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};