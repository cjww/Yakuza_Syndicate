#include "Image.h"

Image::Image(const sf::Texture& texture, const UIVisualSettings& visuals) : UIElement(visuals) {
	sprite.setTexture(texture);
}

Image::Image(const sf::Texture& texture, sf::IntRect textureRect, const UIVisualSettings& visuals) : Image(texture, visuals){
	sprite.setTextureRect(textureRect);
}

sf::Vector2f Image::getPosition() const {
	return sprite.getPosition();
}

void Image::setPosition(sf::Vector2f position) {
	sprite.setPosition(position);
	setChildrenPosition(position);
}

sf::FloatRect Image::getBounds() const {
	return sprite.getGlobalBounds();
}


void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
	drawChildren(target, states);
}
