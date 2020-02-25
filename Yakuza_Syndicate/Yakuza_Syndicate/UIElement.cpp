#include "UIElement.h"


UIElement::UIElement() : GameEntity(){

}

UIElement::UIElement(sf::Texture& texture) : GameEntity(texture){

}

UIElement::~UIElement() {
	for (auto& child : children) {
		delete child;
	}
}

UIElement* UIElement::addChild(UIElement* elem) {
	children.push_back(elem);
	elem->parent = this;
	return elem;
}

void UIElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw((GameEntity)*this);
	for (const auto& child : children) {
		target.draw(*child);
	}
}
