#include "Button.h"

Button::Button(const UIVisualSettings& visuals) : Pane(sf::Vector2f(50, 50), visuals) {
	paddingLeft = 0;
	paddingTop = 0;
	label = nullptr;
	
}

Button::Button(const char* labelString, const UIVisualSettings& visuals) : Pane(visuals) {
	label = new Label(labelString, visuals);
	addChild(label);
	paddingLeft = 25;
	paddingTop = 20;
	setSize(sf::Vector2f(label->getBounds().width + paddingLeft * 2, label->getBounds().height + paddingTop * 2));
}

Button::Button(const char* labelString, sf::Vector2f size, const UIVisualSettings& visuals) : Button(labelString, visuals){
	setSize(size);
	sf::Vector2f labelSize(label->getBounds().width, label->getBounds().height);
	paddingLeft = size.x / 2 - labelSize.x / 2;
	paddingTop = size.y / 2 - labelSize.y / 2;
}

void Button::setPosition(sf::Vector2f position) {
	Pane::setPosition(position);
	setChildrenPosition(position);
	if(label != nullptr) label->setPosition(position + sf::Vector2f(paddingLeft, paddingTop - 5.f));
}

bool Button::contains(sf::Vector2f point) {
	return getBounds().contains(point);
}

void Button::setVisuals(const UIVisualSettings& visuals) {
	Pane::setVisuals(visuals);
	if(label != nullptr) label->setVisuals(visuals);
}

Label* Button::getLabel() const {
	return label;
}
