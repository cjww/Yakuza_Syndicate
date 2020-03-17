#include "GangMembers.h"

GangMembers::GangMembers(int amount)
	:GameEntity(ResourceManager::getTexture("GangMembers"))
{

	this->amount = amount;
	this->upkeep = 7.5;
	action = true;
	inFriendlyTerr = true;
	inBuildingState = false;	this->font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	this->text.setFont(font);

	this->text.setString(std::to_string(amount));
	this->text.setFillColor(sf::Color::Magenta);
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(2);

}

GangMembers::GangMembers(const GangMembers& other) : GameEntity(other) {
	this->amount = other.amount;
	this->action= other.action;
	this->inFriendlyTerr = other.inFriendlyTerr;	this->text = other.text;
	this->font = other.font;
	this->font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	this->text.setFont(this->font);

}

GangMembers& GangMembers::operator=(const GangMembers& other) {

	this->amount = other.amount;
	this->action = other.action;
	this->inFriendlyTerr = other.inFriendlyTerr;	this->text = other.text;
	this->text.setFont(this->font);
	
	setPosition(other.getPosition());

	return *this;
}

bool GangMembers::merge(GangMembers& other)
{
	bool merged = false;
	if (this->amount + other.amount < 65)
	{
		this->amount += other.amount;
		other.amount = 0;
		other.text.setString(std::to_string(other.amount));
		this->text.setString(std::to_string(this->amount));
		merged = true;
	}
	return merged;
}

int GangMembers::getUpkeep()
{
	return amount * upkeep;
}

int GangMembers::getAmount()
{
	return amount;
}

void GangMembers::setAmount(int amount)
{
	this->amount = amount;
	text.setString(std::to_string(amount));
}

bool GangMembers::hasAction()
{
	return action;
}

void GangMembers::setHasAction(bool action)
{
	this->action = action;
	if (!action)
	{
		text.setFillColor(sf::Color(200, 200, 200));
	}
	else
	{
		text.setFillColor(sf::Color::Magenta);
	}
}

void GangMembers::setInFriendlyTerr(bool inFriendlyTerr)
{
	this->inFriendlyTerr = inFriendlyTerr;
}

void GangMembers::fight(GangMembers &other)
{
	float strThis = this->amount;
	float strOther = other.amount;
	if (this->inFriendlyTerr)
	{
		strOther *= 0.75f;
	}
	if (other.inFriendlyTerr)
	{
		strThis *= 0.75f;
	}

	if (strThis < strOther)
	{
		strOther -= strThis;
		other.amount = strOther;
		this->amount = 0;
			
	}
	else if (strThis > strOther)
	{
		strThis -= strOther;
		this->amount = strThis;
		other.amount = 0;
	}
	else
	{
		this->amount = 0;
		other.amount = 0;
	}
	other.text.setString(std::to_string(other.amount));
	this->text.setString(std::to_string(this->amount));
}

GangMembers * GangMembers::split(int amountToSplit)
{
	GangMembers* newgm = new GangMembers(amountToSplit);
	newgm->setPosition(getPosition());
	setAmount(this->amount - amountToSplit);
	return newgm;
}

void GangMembers::setPosition(sf::Vector2f pos) {
	GameEntity::setPosition(pos);
	if (getOwner() == Owner::PLAYER2)
	{
		this->text.setPosition(pos + sf::Vector2f(32, 0));
	}
	else {
		this->text.setPosition(pos);
	}
}

void GangMembers::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GameEntity::draw(target, states);

	target.draw(this->text, states);
}

void GangMembers::setIsBuilding(bool value) {
	this->inBuildingState = value;
}

bool GangMembers::getIsBuilding() const {
	return inBuildingState;
}

bool GangMembers::isInTerr() const {
	return this->inFriendlyTerr;
}

void GangMembers::update() {
	//Set sprite
	setTexture(ResourceManager::getTexture("GangMembers"));
	if (inBuildingState) {
		//Animate
		animate(&ResourceManager::getTexture("Hammer"), 32, 3, 0.15f);
	}
}


