#pragma once
#include "GameEntity.h"

class Bank : public GameEntity {
private:
	int security;
public:
	Bank();

	int heist();
};