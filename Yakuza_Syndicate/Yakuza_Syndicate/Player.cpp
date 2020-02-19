#include "Player.h"

Player::Player(GameField* gameField)
	: endTurn(false),
	color(sf::Color::Black),
	territory(gameField),
	gameField(gameField)
{

	territory.setColor(color);
	balance = 0;
}

void Player::mousePressed(sf::Vector2i mousePosition, sf::Mouse::Button button) {
	//TODO check if button was pressed
	//endTurn = true;
	if (button == sf::Mouse::Button::Left) {
		Tile* clickedTile = gameField->getTileAt((sf::Vector2f)mousePosition);
		if (clickedTile != nullptr) {
			territory.buildDojo(clickedTile->getPosition());
		}
	}
	else {
		endTurn = true;
	}
}

void Player::update() {
	
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(territory);
}

bool Player::getEndTurn() const {
	return this->endTurn;
}

void Player::setEndTurn(bool value) {
	endTurn = value;
}

void Player::setColor(sf::Color color) {
	this->color = color;
	territory.setColor(color);
}
