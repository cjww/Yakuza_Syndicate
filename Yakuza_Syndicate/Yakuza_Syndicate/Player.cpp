#include "Player.h"

Player::Player(GameField* gameField, Owner owner, sf::RenderWindow& window)
	: endTurn(false),
	color(sf::Color::Black),
	territory(gameField, owner),
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
	selectedGmAmount = 0;
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

	UIVisualSettings vis = {};
	vis.textFillColor = sf::Color::White;
	vis.textOutlineColor = sf::Color::Black;
	vis.textOutlineThickness = 1;
	selectedGmLabel = new Label("", vis);

	
	if (owner == Owner::PLAYER2) {
		uiPane.setPosition(sf::Vector2f(1450, 0));
		uiPane.setVisuals(uiInactiveVis);
	}

}

Player::Player(const Player& otherPlayer) : Player(otherPlayer.gameField, otherPlayer.playernr, otherPlayer.window)
{
	
}

Player::~Player() {
	delete selectedGmLabel;
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
			endTurn = true;
		}
		if (canBuildDojo) {
			if (buildDojoBtn->contains(mousePosition)) {
				Message msg;
				msg.type = MessageType::DOJO_BUILT;
				msg.vec2[0] = selectedGM->getPosition();
				NetworkManager::send(msg);
				territory.buildDojo(selectedGM->getPosition());
				selectedGM->setIsBuilding(true);
				balance -= 1000;
				balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
				selectedGM->setHasAction(false);
				selectedGM->setInFriendlyTerr(true);
			}
		}
		if (canMakeHeist) {
			if (makeHeistBtn->contains(mousePosition)) {
				Message msg;
				msg.type = MessageType::MADE_HEIST;
				NetworkManager::send(msg);
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
							selectedGmAmount = gangMembers[i]->getAmount();
							selectedGmLabel->setString("Selected: < " + std::to_string(selectedGmAmount) + " >");
							selectedGmLabel->setPosition(selectedGM->getPosition() + sf::Vector2f(-64, 64));

							std::set<Tile*> findBuilding = gameField->getSurroundingTiles(selectedTile);
							bool foundBuilding = false;
							for (const auto& tile : findBuilding)
							{
								if (tile->getBuilding() != nullptr)
								{
									foundBuilding = true;
								}
							}

							bool tooCloseToMid = false;
							for (i = 0; i < 15 && !tooCloseToMid; i++)
							{
								if (gameField->lengthOfVector(gameField->getTileByIndex(i, i)->getPosition() - selectedTile->getPosition()) <
									selectedTile->getGlobalBounds().width * 2)
								{
									tooCloseToMid = true;
								}
							}
							if (selectedGM->getAmount() >= 10 &&
								!foundBuilding && !tooCloseToMid &&
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
					if (selectedGM->hasAction() /*&&
						gameField->lengthOfVector(selectedGM->getPosition() - selectedTile->getPosition()) <= selectedTile->getGlobalBounds().width*/)
					{
						bool split = false;
						if (selectedGmAmount < selectedGM->getAmount())
						{
							selectedGM = selectedGM->split(selectedGmAmount);
							gangMembers.push_back(selectedGM);
							if (this->playernr == Owner::PLAYER2)
							{
								selectedGM->flipSprite();
							}
							split = true;
						}
						if (toMerge == nullptr)
						{
							
							Message msg;
							if (!split) {
								msg.type = MessageType::GANGMEMBER_MOVED;
								msg.vec2[0] = selectedGM->getPosition();
								gameField->getTileAt(selectedGM->getPosition())->setGangMembers(nullptr);
							}
							else {
								msg.type = MessageType::GANGMEMBER_SPLIT;
								msg.vec2[0] = selectedGM->getPosition();
								msg.i = selectedGmAmount;
							}
							selectedGM->setPosition(selectedTile->getPosition());
							selectedTile->setGangMembers(selectedGM);
							selectedGM->setHasAction(false);
							
							if (!this->territory.checkIfTileInTerr(selectedTile))
							{
								selectedGM->setInFriendlyTerr(false);
							}
							else
							{
								selectedGM->setInFriendlyTerr(true);
							}

							msg.vec2[1] = selectedGM->getPosition();
							NetworkManager::send(msg);
							
						}
						else
						{
							if (toMerge->merge(*selectedGM))
							{

								Message msg;
								msg.type = MessageType::GANGMEMBER_SPLIT;
								msg.i = selectedGmAmount;
								if (!split) {
									msg.type = MessageType::GANGMEMBER_MOVED;
									gameField->getTileAt(selectedGM->getPosition())->setGangMembers(nullptr);
								}
								msg.vec2[0] = selectedGM->getPosition();
								msg.vec2[1] = toMerge->getPosition();
								NetworkManager::send(msg);

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

void Player::keyPressed(sf::Keyboard::Key key)
{
	if (selectedGM != nullptr)
	{
		if (key == sf::Keyboard::Left && selectedGmAmount > 1)
		{
			selectedGmAmount--;
		}
		else if (key == sf::Keyboard::Right && selectedGmAmount < selectedGM->getAmount())
		{
			selectedGmAmount++;
		}
		selectedGmLabel->setString("Selected: < " + std::to_string(selectedGmAmount) + " >");
	}
}

void Player::update() 
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(territory, &shader);
	for (const auto& gm : gangMembers) {
		target.draw(*gm, &shader);
	}
	if (selectedTile != nullptr) {
		target.draw(selectedTileRect);
	}
	if (selectedGM != nullptr)
	{
		target.draw(*selectedGmLabel);
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
		else if (gangMembers[i]->getIsBuilding()) {
			gangMembers[i]->setIsBuilding(false);
		}
	}

	balance += territory.getIncome();
	balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
	
	std::vector<GangMembers*> newGangMembers = territory.getNewGangMembers();

	income = territory.getIncome();
	incomeLabel->setString("Income: " + std::to_string(income) + " Yen");

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

sf::Color Player::getColor()
{
	return color;
}

bool Player::checkIfWin()
{
	bool won = false;
	for (int i = 0; i < gangMembers.size() && !won; i++)
	{
		if ((int)playernr == 0)
		{
			if (gangMembers[i]->getPosition() == gameField->getTileByIndex(14, 0)->getPosition())
			{
				won = true;
			}
		}
		else
		{
			if (gangMembers[i]->getPosition() == gameField->getTileByIndex(0, 14)->getPosition())
			{
				won = true;
			}
		}
	}
	return won;
}

void Player::proccessMessage(Message& msg) {
	switch (msg.type) {
	case MessageType::COLOR_CHANGED:
		setColor(msg.color);
		break;
	case MessageType::DOJO_BUILT:
	{
		territory.buildDojo(msg.vec2[0]);
		balance -= 1000;
		balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
		GangMembers* gm = getGMAtPos(msg.vec2[0]);
		gm->setHasAction(false);
		gm->setInFriendlyTerr(true);
		gm->setIsBuilding(true);
		break;
	}
	case MessageType::GANGMEMBER_MOVED:
	{
		GangMembers* gm = getGMAtPos(msg.vec2[0]);
		gameField->getTileAt(gm->getPosition())->setGangMembers(nullptr);
		GangMembers* targetGm = getGMAtPos(msg.vec2[1]);
		if (targetGm != nullptr) {
			targetGm->merge(*gm);
			removeGM(gm);
		}
		else {
			gm->setPosition(msg.vec2[1]);
			gameField->getTileAt(gm->getPosition())->setGangMembers(gm);
		}
		if (!this->territory.checkIfTileInTerr(gameField->getTileAt(gm->getPosition())))
		{
			gm->setInFriendlyTerr(false);
		}
		else
		{
			gm->setInFriendlyTerr(true);
		}
		break;
	}
	case MessageType::GANGMEMBER_SPLIT:
	{
		GangMembers* gm = getGMAtPos(msg.vec2[0]);
		gm = gm->split(msg.i);
		GangMembers* targetGm = getGMAtPos(msg.vec2[1]);
		if (targetGm != nullptr) {
			targetGm->merge(*gm);
			targetGm->setHasAction(false);
			delete gm;
		}
		else {
			gangMembers.push_back(gm);
			gm->setPosition(msg.vec2[1]);
			gameField->getTileAt(gm->getPosition())->setGangMembers(gm);
			gm->setHasAction(false);

			if (this->playernr == Owner::PLAYER2)
			{
				gm->flipSprite();
			}
			if (!this->territory.checkIfTileInTerr(gameField->getTileAt(gm->getPosition())))
			{
				gm->setInFriendlyTerr(false);
			}
			else
			{
				gm->setInFriendlyTerr(true);
			}
		}

		break;
	}
	case MessageType::MADE_HEIST:
	{
		GangMembers* gm = getGMAtPos(gameField->getTileByIndex(14, 14)->getPosition());
		balance += gm->getAmount() * 100;
		balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
		gameField->makeHeist(gm);
		gm->setHasAction(false);
		break;
	}
	case MessageType::END_TURN:
		endTurn = true;
		break;
	}
}
