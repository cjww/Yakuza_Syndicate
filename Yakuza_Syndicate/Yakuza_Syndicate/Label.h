#pragma once
#include "UIElement.h"
class Label : public UIElement {
private:
	sf::Font font;
	sf::Text text;
public:
	Label(const char* str);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};