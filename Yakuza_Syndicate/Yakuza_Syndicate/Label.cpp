#include "Label.h"

Label::Label(std::string str, const UIVisualSettings& visuals) : UIElement(visuals) {
	setVisuals(visuals);
	text.setFont(font);
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

std::string Label::getString() const {
	return text.getString();
}

sf::FloatRect Label::getBounds() const {
	return text.getGlobalBounds();
}

void Label::setVisuals(const UIVisualSettings& visuals) {
	font.loadFromFile(visuals.textFont);
	text.setFillColor(visuals.textFillColor);
	text.setOutlineColor(visuals.textOutlineColor);
	text.setCharacterSize(visuals.textSize);
	text.setOutlineThickness(visuals.textOutlineThickness);
	UIElement::setVisuals(visuals);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
	drawChildren(target, states);
}
