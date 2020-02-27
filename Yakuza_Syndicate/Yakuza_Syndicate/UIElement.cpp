#include "UIElement.h"


UIElement::UIElement(const UIVisualSettings& visuals) {
	this->offsetToParrent = sf::Vector2f(0, 0);
	this->parent = nullptr;
}

UIElement::UIElement(const UIElement& other) {
	this->children = other.children;
	this->parent = other.parent;
	this->offsetToParrent = other.offsetToParrent;
}

UIElement::~UIElement() {
	for (auto& child : children) {
		delete child;
	}
}

UIElement* UIElement::addChild(UIElement* elem, sf::Vector2f offset) {
	children.push_back(elem);
	elem->parent = this;
	elem->offsetToParrent = offset;
	elem->setPosition(elem->parent->getPosition() + elem->offsetToParrent);
	return elem;
}

void UIElement::setChildrenPosition(sf::Vector2f parentPosition) {
	for (const auto& child : children) {
		child->setPosition(parentPosition + child->offsetToParrent);
	}
}

void UIElement::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& child : children) {
		target.draw(*child, states);
	}
}

void UIElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	drawChildren(target, states);
}
