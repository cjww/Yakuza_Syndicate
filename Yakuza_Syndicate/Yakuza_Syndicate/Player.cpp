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

	katanaSound.setBuffer(ResourceManager::getSoundBuffer("Katana"));

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
	for (int i = 0; i < gangMembers.size() && !removed; i++)
	{
		if (toRemove == gangMembers[i])
		{
			delete gangMembers[i];
			gangMembers.erase(gangMembers.begin() + i);
			removed = true;
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
				buildDojo(selectedGM);
			}
		}
		if (canMakeHeist) {
			if (makeHeistBtn->contains(mousePosition)) {
				Message msg;
				msg.type = MessageType::MADE_HEIST;
				NetworkManager::send(msg);
				makeHeist(selectedGM);
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
			else if (tilePtr != nullptr) 
			{	
				if (selectedGM != nullptr) //do someting with selected GangMembers
				{
					if (selectedGM->hasAction() /*&&
						gameField->lengthOfVector(selectedGM->getPosition() - selectedTile->getPosition()) <= selectedTile->getGlobalBounds().width*/)
					{
						
						Message msg;
						msg.type = MessageType::GANGMEMBER_MOVED;
						msg.vec2[0] = selectedGM->getPosition();
						msg.vec2[1] = tilePtr->getPosition();
						msg.i = selectedGmAmount;
						
						if (moveGM(selectedGM, selectedGmAmount, tilePtr)) {
							NetworkManager::send(msg);
						}
					}
					selectedTile = nullptr;
					selectedGM = nullptr;
				}
				else 
				{
					selectTile(tilePtr);
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

void Player::drawTerritory(sf::RenderWindow& window) {
	window.draw(this->territory, &shader);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
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
			gangMembers[i]->setInFriendlyTerr(true);
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
		buildDojo(getGMAtPos(msg.vec2[0]));
		break;
	}
	case MessageType::GANGMEMBER_MOVED:
	{
		GangMembers* gmToMove = getGMAtPos(msg.vec2[0]);
		Tile* toTile = gameField->getTileAt(msg.vec2[1]);
		moveGM(gmToMove, msg.i, toTile);
		break;
	}
	case MessageType::MADE_HEIST:
	{
		GangMembers* gm = getGMAtPos(gameField->getTileByIndex(14, 14)->getPosition());
		makeHeist(gm);
		break;
	}
	case MessageType::END_TURN:
		endTurn = true;
		break;
	}
}

void Player::buildDojo(GangMembers* gm)
{
	territory.buildDojo(gm->getPosition());
	gm->setIsBuilding(true);
	balance -= 1000;
	balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
	gm->setHasAction(false);
}

void Player::makeHeist(GangMembers* gm)
{
	balance += gm->getAmount() * 100;
	balanceLabel->setString("Balance: " + std::to_string(balance) + " Yen");
	gameField->makeHeist(gm);
	gm->setHasAction(false);
}

bool Player::selectTile(Tile* tile) {
	this->selectedTile = tile;
	selectedTileRect.setPosition(selectedTile->getPosition());
	selectedTileRect.setSize(sf::Vector2f(selectedTile->getGlobalBounds().width, selectedTile->getGlobalBounds().height));
	selectedTileRect.setFillColor(sf::Color::Transparent);
	selectedTileRect.setOutlineColor(color);
	selectedTileRect.setOutlineThickness(1);
	
	GangMembers* gmAtTile = getGMAtPos(tile->getPosition());
	if (gmAtTile != nullptr) {
		selectedGM = gmAtTile;
		selectedGmAmount = selectedGM->getAmount();
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
		for (int i = 0; i < 15 && !tooCloseToMid; i++)
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

	return false;
}

GangMembers* Player::trySplitGM(GangMembers* gm, int amount) {
	GangMembers* newGm = nullptr;
	if (amount < gm->getAmount())
	{
		newGm = gm->split(amount);
		if (this->playernr == Owner::PLAYER2)
		{
			newGm->flipSprite();
		}
		newGm->setOwner(playernr);
	}
	return newGm;
}

bool Player::moveGM(GangMembers* gmToMove, int amount, Tile* toTile) {
	bool success = true;
	Tile* fromTile = gameField->getTileAt(gmToMove->getPosition());
	GangMembers* gm = trySplitGM(gmToMove, amount);
	bool hasSplit = false;
	if (gm != nullptr) { //if split was needed
		gmToMove = gm;
		hasSplit = true;
	}
	GangMembers* toMerge = toTile->getGangMembers();
	if (toMerge != nullptr) {
		if (toMerge->getOwner() != playernr) {
			katanaSound.play();
			gmToMove->setPosition(toTile->getPosition());
			if (!hasSplit) {
				fromTile->setGangMembers(nullptr);
			}
			else {
				gangMembers.push_back(gmToMove);
			}
			toTile->setGangMembers(gmToMove);
		}
		else {
			if (toMerge->merge(*gmToMove)) { //If merge was successfull
				if (!hasSplit) {
					fromTile->setGangMembers(nullptr);
					removeGM(gmToMove);
				}
				else {
					delete gmToMove;
				}
				gmToMove = toMerge;
			}
			else if (hasSplit) {
				delete gm;
				success = false;
			}
			else {
				success = false;
			}
		}
	}
	else {
		gmToMove->setPosition(toTile->getPosition());
		toTile->setGangMembers(gmToMove);
		gmToMove->setInFriendlyTerr(territory.checkIfTileInTerr(toTile));
		if (!hasSplit) {
			fromTile->setGangMembers(nullptr);
		}
		else {
			gangMembers.push_back(gmToMove);
		}
	}
	gmToMove->setHasAction(false);
	return success;
}
