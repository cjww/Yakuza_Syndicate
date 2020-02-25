#include "Player.h"

Player::Player(GameField* gameField, int playernr)
	: endTurn(false),
	color(sf::Color::Black),
	territory(gameField),
	gameField(gameField),
	playernr(playernr)
{

	territory.setColor(color);
	selectedTile = nullptr;
	balance = 0;
	shader.loadFromFile("../res/fragmentShader.glsl", sf::Shader::Type::Fragment);
	
}

Player::Player(const Player& otherPlayer) : Player(otherPlayer.gameField, otherPlayer.playernr)
{

}

void Player::mousePressed(sf::Vector2f mousePosition, sf::Mouse::Button button) {
	//TODO check if button was pressed
	//endTurn = true;
	std::cout << mousePosition.x << ", " << mousePosition.y << std::endl;

	if (button == sf::Mouse::Button::Left) {
		territory.buildDojo(mousePosition);
		Tile* tilePtr = this->gameField->getTileAt(mousePosition);
		if(tilePtr != nullptr)
		{
			this->selectedTile = tilePtr;
			selectedTileRect.setPosition(tilePtr->getPosition());
			selectedTileRect.setSize(sf::Vector2f(tilePtr->getGlobalBounds().width,tilePtr->getGlobalBounds().height));
			selectedTileRect.setFillColor(sf::Color::Transparent);
			selectedTileRect.setOutlineColor(color);
			selectedTileRect.setOutlineThickness(1);
		}
	}
	else {
		turnEnd();
	}

}

void Player::update() {
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(territory, &shader);
	for (const auto& gm : gangMembers) {
		target.draw(gm, &shader);
		gm.drawText(target, shader);
	}
	target.draw(selectedTileRect);
}

bool Player::wantsToEndTurn() const {
	return this->endTurn;
}

void Player::turnEnd() {
	endTurn = true;

}

void Player::turnStart() {
	endTurn = false;
	std::vector<GangMembers> newGangMembers = territory.getNewGangMembers();
	for (auto& newGm : newGangMembers) { // loop all new GangMembers
		bool found = false;
		for (auto& myGm : gangMembers) { // check for any preexisting gangMember on same position
			if (myGm.getPosition() == newGm.getPosition()) {
				if (!myGm.merge(newGm)) {
					int diff = abs(64 - myGm.getAmount());
					GangMembers diffGm(diff);
					myGm.merge(diffGm);
				}
				found = true;
			}
		}
		if (!found) { // no preexisting gangMemebr at position
			if (this->playernr == 1)
			{
				newGm.flipSprite();
			}
			gangMembers.push_back(newGm);
		}
	}
}

void Player::setColor(sf::Color color) {
	this->color = color;
	territory.setColor(color);
	shader.setUniform("teamColor", sf::Glsl::Vec4(color));
}
