#include "Label.h"

Label::Label(const char* str, const UIVisualSettings& visuals) : UIElement(visuals) {
	font.loadFromFile(visuals.textFont);

	text.setFont(font);
	text.setFillColor(visuals.textFillColor);
	text.setOutlineColor(visuals.textOutlineColor);
	text.setCharacterSize(visuals.textSize);
	text.setOutlineThickness(visuals.textOutlineThickness);
	text.setString(str);
}

sf::Vector2f Label::getPosition() const {
	return text.getPosition();
}

void Label::setPosition(sf::Vector2f position) {
	text.setPosition(position);
	setChildrenPosition(position);
}

void Label::setString(const std::string& string) {
	text.setString(string);
}

sf::FloatRect Label::getBounds() const {
	return text.getGlobalBounds();
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
	drawChildren(target, states);
}
