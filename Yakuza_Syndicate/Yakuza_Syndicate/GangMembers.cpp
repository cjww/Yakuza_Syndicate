#include "GangMembers.h"

GangMembers::GangMembers(int amount)
	:GameEntity(*ResourceManager::getTexture("GangMembers"))
{

	this->amount = amount;
	action = true;
	inFriendlyTerr = true;
	this->font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
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

int GangMembers::getAmount()
{
	return amount;
}

bool GangMembers::hasAction()
{
	return action;
}

void GangMembers::setHasAction(bool action)
{
	this->action = action;
}

void GangMembers::setInFriendlyTerr(bool inFriendlyTerr)
{
	this->inFriendlyTerr = inFriendlyTerr;
}

void GangMembers::fight(GangMembers &other)
{
	int strThis = this->amount;
	int strOther = other.amount;
	if (this->inFriendlyTerr)
	{
		strThis *= 1.5;
	}
	else if (other.inFriendlyTerr)
	{
		strOther *= 1.5;
	}

	if (strThis < strOther)
	{
		other.amount -= strThis;
		this->amount = 0;
			
	}
	else if (strThis > strOther)
	{
		this->amount -= strOther;
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

void GangMembers::setTextPos(sf::Vector2f pos) 
{
	this->text.setPosition(pos);
}


void GangMembers::drawText(sf::RenderTarget& target, const sf::Shader& shader) const 
{
	target.draw(this->text, &shader);
}

