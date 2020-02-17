#include "Player.h"

Player::Player() : endTurn(false), color(sf::Color::Black){

}

void Player::mousePressed(sf::Vector2i mousePosition) {
	//TODO check if button was pressed
	endTurn = true;
}

void Player::update() {
	std::cout << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << std::endl;
	
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}

bool Player::getEndTurn() const {
	return this->endTurn;
}

void Player::setEndTurn(bool value) {
	endTurn = value;
}

void Player::setColor(sf::Color color) {
	this->color = color;
}
