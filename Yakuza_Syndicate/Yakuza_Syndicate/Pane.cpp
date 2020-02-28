#include "Pane.h"

Pane::Pane(const UIVisualSettings& visuals) : UIElement(visuals) {
	shape.setFillColor(visuals.rectFillColor);
	shape.setOutlineColor(visuals.rectOutlineColor);
	shape.setOutlineThickness(visuals.rectOutlineThicknes);
}

Pane::Pane(sf::Vector2f size, const UIVisualSettings& visuals) : Pane(visuals) {
	shape.setSize(size);
}

void Pane::setPosition(sf::Vector2f position) {
	shape.setPosition(position);
	setChildrenPosition(position);
}

sf::Vector2f Pane::getPosition() const {
	return shape.getPosition();
}

sf::FloatRect Pane::getBounds() const {
	return shape.getGlobalBounds();
}

void Pane::setSize(sf::Vector2f size){
	shape.setSize(size);
}

void Pane::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(shape);
	drawChildren(target, states);
}