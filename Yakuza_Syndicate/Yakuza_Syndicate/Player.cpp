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
	selectedGM = nullptr;
	balance = 0;
	shader.loadFromFile("../res/fragmentShader.glsl", sf::Shader::Type::Fragment);
	
	UIVisualSettings uiVis = {};
	uiVis.rectFillColor = sf::Color::Yellow;
	uiVis.textFillColor = sf::Color::Magenta;
	uiVis.textOutlineThickness = 1;

	uiPane.addChild((endTurnBtn = new Button("End Turn", uiVis)), sf::Vector2f(600, 200));
}

Player::Player(const Player& otherPlayer) : Player(otherPlayer.gameField, otherPlayer.playernr)
{

}

void Player::mousePressed(sf::Vector2f mousePosition, sf::Mouse::Button button) {
	//TODO check if button was pressed
	if (endTurnBtn->contains(mousePosition)) {
		turnEnd();
	}

	if (button == sf::Mouse::Button::Left) {
		//territory.buildDojo(mousePosition);
		Tile* tilePtr = this->gameField->getTileAt(mousePosition);
		if(tilePtr != nullptr)
		{
			if (tilePtr == this->selectedTile)
			{
				selectedTile = nullptr;
			}
			else
			{
				this->selectedTile = tilePtr;
				selectedTileRect.setPosition(tilePtr->getPosition());
				selectedTileRect.setSize(sf::Vector2f(tilePtr->getGlobalBounds().width, tilePtr->getGlobalBounds().height));
				selectedTileRect.setFillColor(sf::Color::Transparent);
				selectedTileRect.setOutlineColor(color);
				selectedTileRect.setOutlineThickness(1);

				bool foundGM = false;
				for (int i = 0; i < this->gangMembers.size(); i++)
				{
					if (gangMembers[i].getPosition() == selectedTile->getPosition())
					{
						selectedGM = &gangMembers[i];
						foundGM = true;
					}
				}
				if (!foundGM && selectedGM != nullptr && selectedGM->hasAction() &&
					sqrt(pow(selectedTile->getGlobalBounds().left - selectedGM->getGlobalBounds().left, 2) + 
					pow(selectedTile->getGlobalBounds().top - selectedGM->getGlobalBounds().top, 2)) <= selectedTile->getGlobalBounds().width)
				{
					selectedGM->setPosition(selectedTile->getPosition());
					selectedGM->setTextPos(selectedGM->getPosition());
					selectedGM->setAction(false);
					selectedTile = nullptr;
					selectedGM = nullptr;
				}
			}
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
	if (selectedTile != nullptr) {
		target.draw(selectedTileRect);
	}
	target.draw(uiPane, &shader);
}

bool Player::wantsToEndTurn() const {
	return this->endTurn;
}

void Player::turnEnd() {
	endTurn = true;
	this->selectedTile = nullptr;
	for (int i = 0; i < gangMembers.size(); i++)
	{
		gangMembers[i].setAction(true);
	}
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
