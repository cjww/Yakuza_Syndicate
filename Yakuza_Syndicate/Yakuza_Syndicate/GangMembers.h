#pragma once
#include "GameEntity.h"

class GangMembers : public GameEntity {
private:
	sf::Text text;
	sf::Font font;

	int amount;
	bool action;
	bool inFriendlyTerr;

public:
	GangMembers(int amount);
	GangMembers(const GangMembers& other);
	GangMembers& operator=(const GangMembers& other);

	
	bool merge(GangMembers& other);
	int getAmount();
	bool hasAction();
	void setAction(bool action);
	void fight(GangMembers &other);

	void setTextPos(sf::Vector2f pos);

	void drawText(sf::RenderTarget& target, const sf::Shader& shader) const;
};