#include "Player.h"

Player::Player(GameField* gameField)
	: endTurn(false),
	color(sf::Color::Black),
	territory(gameField),
	gameField(gameField)
{

	territory.setColor(color);
	balance = 0;
	shader.loadFromFile("../res/fragmentShader.glsl", sf::Shader::Type::Fragment);
	
}

void Player::mousePressed(sf::Vector2f mousePosition, sf::Mouse::Button button) {
	//TODO check if button was pressed
	//endTurn = true;
	std::cout << mousePosition.x << ", " << mousePosition.y << std::endl;
	if (button == sf::Mouse::Button::Left) {
		territory.buildDojo(mousePosition);
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
		for (auto& myGm : gangMembers) { // check for any preexcisting gangMember on same position
			if (myGm.getPosition() == newGm.getPosition()) {
				if (!myGm.merge(newGm)) {
					int diff = abs(64 - myGm.getAmount());
					GangMembers diffGm(diff);
					myGm.merge(diffGm);
				}
				found = true;
			}
		}
		if (!found) { // no preexcisting gangMemebr att position
			gangMembers.push_back(newGm);
		}
	}
}

void Player::setColor(sf::Color color) {
	this->color = color;
	territory.setColor(color);
	shader.setUniform("teamColor", sf::Glsl::Vec4(color));
}
