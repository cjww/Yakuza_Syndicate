#pragma once
#include "GameEntity.h"

class GangMembers : public GameEntity {
private:
	sf::Text text;
	sf::Font font;

	int amount;
	bool inBuilding;
	bool inFriendlyTerr;

public:
	GangMembers(int amount);
	GangMembers(const GangMembers& other);
	GangMembers& operator=(const GangMembers& other);

	
	bool merge(GangMembers& other);
	int getAmount();
	void fight(GangMembers &other);

	void setTextPos(sf::Vector2f pos);
<<<<<<< HEAD
	void drawText(sf::RenderTarget& target) const;
=======
	void drawText(sf::RenderTarget& target, const sf::Shader& shader) const;
>>>>>>> 73ef86a53c2383dbcc9d813e16688108a9a74cc6
};