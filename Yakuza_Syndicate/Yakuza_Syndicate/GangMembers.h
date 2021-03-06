#pragma once
#include "GameEntity.h"

class GangMembers : public GameEntity {
private:
	sf::Text text;
	sf::Font font;

	int amount;
	float upkeep;
	bool action;
	bool inFriendlyTerr;

	bool inBuildingState;

public:
	GangMembers(int amount);
	GangMembers(const GangMembers& other);
	GangMembers& operator=(const GangMembers& other);

	
	bool merge(GangMembers& other);

	int getUpkeep();
	int getAmount();
	void setAmount(int amount);
	bool hasAction();
	void setHasAction(bool action);
	void setInFriendlyTerr(bool inFriendlyTerr);
	void fight(GangMembers &other);
	GangMembers* split(int amountToSplit);

	void setPosition(sf::Vector2f pos) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setIsBuilding(bool value);
	bool getIsBuilding() const;

	bool isInTerr() const;

	void update();
};