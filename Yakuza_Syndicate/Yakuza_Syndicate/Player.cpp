#include "Player.h"

Player::Player(GameField* gameField, Owner owner, sf::RenderWindow& window)
	: endTurn(false),
	color(sf::Color::Black),
	territory(gameField),
	gameField(gameField),
	playernr(owner),
	window(window),
	canBuildDojo(false),
	canMakeHeist(false)
{

	territory.setColor(color);
	selectedTile = nullptr;
	selectedGM = nullptr;
	balance = 1000;
	income = territory.getIncome();
	shader.loadFromFile("../res/fragmentShader.glsl", sf::Shader::Type::Fragment);
	
	uiActiveVis = {};
	uiActiveVis.rectFillColor = sf::Color::Yellow;
	uiActiveVis.textFillColor = sf::Color::Magenta;
	uiActiveVis.textOutlineThickness = 1;

	uiInactiveVis = {};
	uiInactiveVis.rectFillColor = sf::Color(50, 50, 50);
	uiInactiveVis.textFillColor = sf::Color(100, 100, 100);
	uiInactiveVis.textOutlineThickness = 1;


	uiPane.addChild((incomeLabel = new Label("Income: " + std::to_string(income) + " Yen")), sf::Vector2f(50, 50));
	uiPane.addChild((balanceLabel = new Label("Balance: " + std::to_string(balance) + " Yen")), sf::Vector2f(50, 100));
	uiPane.addChild((totalGmLabel = new Label("Total Gang Members: -")), sf::Vector2f(50, 150));
	uiPane.addChild((gmInCustodyLabel = new Label("Gang Members in Custody: -")), sf::Vector2f(50, 200));
	uiPane.addChild((endTurnBtn = new Button("End Turn", sf::Vector2f(window.getSize().x / 5, 50))), sf::Vector2f(50, 500));
	uiPane.addChild((buildDojoBtn = new Button("Build Dojo", sf::Vector2f(window.getSize().x / 5, 50))), sf::Vector2f(50, 400));
	uiPane.addChild((makeHeistBtn = new Button("Make Heist", sf::Vector2f(window.getSize().x / 5, 50))), sf::Vector2f(50, 300));
	
	if (owner == Owner::PLAYER2) {
		uiPane.setPosition(sf::Vector2f(1450, 0));
		uiPane.setVisuals(uiInactiveVis);
	}

}

Player::Player(const Player& otherPlayer) : Player(otherPlayer.gameField, otherPlayer.playernr, otherPlayer.window)
{
	
}

Player::~Player() {
	for (auto& gm : gangMembers) {
		delete gm;
	}
	gangMembers.clear();
}

void Player::checkFight(Player* other)
{
	for (int i = 0; i < this->gangMembers.size(); i++)
	{
		GangMembers* gmToFight = other->getGMAtPos(gangMembers[i]->getPosition());
		if (gmToFight != nullptr)
		{
			gangMembers[i]->fight(*gmToFight);
			if (gangMembers[i]->getAmount() == 0 && gmToFight->getAmount() == 0)
			{
				gameField->getTileAt(gangMembers[i]->getPosition())->setGangMembers(nullptr);
				this->removeGM(gangMembers[i]);
				other->removeGM(gmToFight);
			}
			else if (gangMembers[i]->getAmount() == 0)
			{
				gameField->getTileAt(gangMembers[i]->getPosition())->setGangMembers(gmToFight);
				this->removeGM(gangMembers[i]);
				i--;
			}
			else if (gmToFight->getAmount() == 0)
			{
				other->removeGM(gmToFight);
				gameField->getTileAt(gangMembers[i]->getPosition())->setGangMembers(gangMembers[i]);
			}
		}
	}
}

void Player::removeGM(GangMembers* toRemove)
{
	bool removed = false;
	for (int i = 0; i < gangMembers.size(); i++)
	{
		if (toRemove == gangMembers[i])
		{
			delete gangMembers[i];
			gangMembers.erase(gangMembers.begin() + i);
		}
	}
}

GangMembers* Player::getGMAtPos(sf::Vector2f pos)
{
	GangMembers* gmAtPos = nullptr;
	for (int i = 0; i < this->gangMembers.size() && gmAtPos == nullptr; i++)
	{
		if (gangMembers[i]->getPosition() == pos)
		{
			gmAtPos = gangMembers[i];
		}
	}
	return gmAtPos;
}

void Player::mousePressed(sf::Vector2f mousePosition, sf::Mouse::Button button) {

	if (button == sf::Mouse::Button::Left) {
		if (endTurnBtn->contains(mousePosition)) {
			this->endTurn = true;
		}
		if (canBuildDojo) {
			if (buildDojoBtn->contains(mousePosition)) {
				territory.buildDojo(selectedGM->getPosition());
				balance -= 1000;
				balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
				income = territory.getIncome();
				incomeLabel->setString("Income: " + std::to_string(income) + " Yen");
				selectedGM->setHasAction(false);
				selectedGM->setInFriendlyTerr(true);
			}
		}
		if (canMakeHeist) {
			if (makeHeistBtn->contains(mousePosition)) {
				balance += selectedGM->getAmount() * 100;
				balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
				gameField->makeHeist(selectedGM);
				selectedGM->setHasAction(false);
			}
		}
		canBuildDojo = false;
		buildDojoBtn->setVisuals(uiInactiveVis);
		canMakeHeist = false;
		makeHeistBtn->setVisuals(uiInactiveVis);

		Tile* tilePtr = this->gameField->getTileAt(mousePosition);
		if(tilePtr != nullptr)
		{
			if (tilePtr == this->selectedTile)
			{
				selectedTile = nullptr;
				selectedGM = nullptr;
			}
			else
			{
				this->selectedTile = tilePtr;
				selectedTileRect.setPosition(tilePtr->getPosition());
				selectedTileRect.setSize(sf::Vector2f(tilePtr->getGlobalBounds().width, tilePtr->getGlobalBounds().height));
				selectedTileRect.setFillColor(sf::Color::Transparent);
				selectedTileRect.setOutlineColor(color);
				selectedTileRect.setOutlineThickness(1);

				
				GangMembers* toMerge = nullptr;
				for (int i = 0; i < this->gangMembers.size(); i++)
				{
					if (gangMembers[i]->getPosition() == selectedTile->getPosition())
					{
						if (selectedGM == nullptr)
						{
							selectedGM = gangMembers[i];
							if (selectedGM->getAmount() >= 10 &&
								selectedTile->getBuilding() == nullptr &&
								selectedGM->hasAction() &&
								balance >= 1000) 
							{
								canBuildDojo = true;
								buildDojoBtn->setVisuals(uiActiveVis);
							}
							if (selectedGM->getAmount() >= 10 &&
								selectedGM->getPosition() == gameField->getTileByIndex(14, 14)->getPosition() &&
								selectedGM->hasAction())
							{
								canMakeHeist = true;
								makeHeistBtn->setVisuals(uiActiveVis);
							}
						}
						else if (gangMembers[i]->getPosition() != selectedGM->getPosition())
						{
							toMerge = gangMembers[i];
						}
						
					}
				}
				
				if (selectedGM != nullptr && selectedGM->getPosition() != selectedTile->getPosition())
				{
					if (selectedGM->hasAction() /*&& sqrt(pow(selectedTile->getGlobalBounds().left - selectedGM->getGlobalBounds().left, 2) +
						pow(selectedTile->getGlobalBounds().top - selectedGM->getGlobalBounds().top, 2)) <= selectedTile->getGlobalBounds().width*/)
					{
						if (toMerge == nullptr)
						{
							gameField->getTileAt(selectedGM->getPosition())->setGangMembers(nullptr);
							selectedGM->setPosition(selectedTile->getPosition());
							selectedTile->setGangMembers(selectedGM);
							//selectedGM->setTextPos(selectedGM->getPosition());

							selectedGM->setHasAction(false);
							Tile* t = gameField->getTileAt(selectedTile->getPosition());
							if (!this->territory.checkIfTileInTerr(selectedTile))
							{
								selectedGM->setInFriendlyTerr(false);
							}
							else
							{
								selectedGM->setInFriendlyTerr(true);
							}
						}
						else
						{
							if (toMerge->merge(*selectedGM))
							{
								toMerge->setHasAction(false);
								bool deleted = false;
								for (int i = 0; i < gangMembers.size() && !deleted; i++)
								{
									if (gangMembers[i] == selectedGM)
									{
										delete gangMembers[i];
										gangMembers.erase(gangMembers.begin() + i);
										deleted = true;
									}
								}
							}
						}
					}
					selectedTile = nullptr;
					selectedGM = nullptr;
					
				}
				
			}
		}
		else
		{
			selectedGM = nullptr;
			selectedTile = nullptr;
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
		target.draw(*gm, &shader);
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
	uiPane.setVisuals(uiInactiveVis);

	for (int i = 0; i < gangMembers.size(); i++)
	{
		if (gangMembers[i]->getAmount() == 0)
		{
			gameField->getTileAt(gangMembers[i]->getPosition())->setGangMembers(nullptr);
			delete gangMembers[i];
			gangMembers.erase(gangMembers.begin() + i);
			i--;
		}
	}

	this->selectedTile = nullptr;
	this->selectedGM = nullptr;
	
	for (int i = 0; i < gangMembers.size(); i++)
	{
		gangMembers[i]->setHasAction(true);
	}
}

void Player::turnStart() {
	endTurn = false;
	uiPane.setVisuals(uiActiveVis);
	buildDojoBtn->setVisuals(uiInactiveVis);
	makeHeistBtn->setVisuals(uiInactiveVis);

	for (int i = 0; i < gangMembers.size(); i++)
	{
		if (gangMembers[i]->getAmount() == 0)
		{
			gameField->getTileAt(gangMembers[i]->getPosition())->setGangMembers(nullptr);
			delete gangMembers[i];
			gangMembers.erase(gangMembers.begin() + i);
			i--;
		}
	}

	balance += territory.getIncome();
	balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");

	std::vector<GangMembers*> newGangMembers = territory.getNewGangMembers();
	for (auto& newGm : newGangMembers) { // loop all new GangMembers
		bool found = false;

		for (auto& myGm : gangMembers) { // check for any preexisting gangMember on same position

			if (myGm->getPosition() == newGm->getPosition()) {
				if (!myGm->merge(*newGm)) {
					int diff = abs(64 - myGm->getAmount());
					GangMembers diffGm(diff);
					myGm->merge(diffGm);
				}
				found = true;
				delete newGm;
			}
		}
		if (!found) { // no preexisting gangMemebr at position
			if (this->playernr == Owner::PLAYER2)
			{
				newGm->flipSprite();
			}
			gangMembers.push_back(newGm);
			gameField->getTileAt(newGm->getPosition())->setGangMembers(newGm);
		}
	}
}

void Player::setColor(sf::Color color) {
	this->color = color;
	territory.setColor(color);
	shader.setUniform("teamColor", sf::Glsl::Vec4(color));
}
