#include "Game.h"

Game::Game() : 
	timePerFrame(sf::seconds(1.0f /60.0f)),
	elapsedTime(sf::Time::Zero), 
	//window(sf::VideoMode(1000, 600), "Yakuza Syndicate")
	window(sf::VideoMode::getFullscreenModes()[0], "Yakuza Syndicate", sf::Style::Fullscreen)
{

	ResourceManager::newTexture("../res/katana_general.png", "GangMembers");
	ResourceManager::newTexture("../res/police_badge.png", "PolicePatrol");
	ResourceManager::newTexture("../res/Dojo_general.png", "Dojo");
	ResourceManager::newTexture("../res/Safe-House_general.png", "SafeHouse");
	ResourceManager::newTexture("../res/Bank.png", "Bank");
	ResourceManager::newTexture("../res/Police-Station.png", "PoliceStation");
	ResourceManager::newTexture("../res/tiles.png", "Tiles");

	gameField = new GameField(window);
	players[0] = new Player(gameField, Owner::PLAYER1, window);
	players[1] = new Player(gameField, Owner::PLAYER2, window);

	players[0]->setColor(sf::Color::Cyan);
	players[1]->setColor(sf::Color::Red);

	turnIndex = 0;
	players[turnIndex]->turnStart();
	
	while (window.isOpen()) {
		handleEvents();
		update();
		draw();
	}
}

Game::~Game() {
	delete gameField;
	delete players[0];
	delete players[1];
}

void Game::handleEvents() {
	sf::Event e;
	while (window.pollEvent(e)) {
		switch(e.type){
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
				players[turnIndex]->mousePressed(sf::Vector2f(e.mouseButton.x, e.mouseButton.y), e.mouseButton.button);
			break;
		}

	}
}

void Game::update() {
	elapsedTime += clock.restart();
	while (elapsedTime > timePerFrame) {
		window.setTitle("FPS: " + std::to_string(1 / elapsedTime.asSeconds()));
		elapsedTime -= timePerFrame;
	
		players[turnIndex]->update();
		if (players[turnIndex]->wantsToEndTurn()) 
		{
			players[turnIndex]->checkFight(players[(turnIndex + 1) % 2]);
			players[turnIndex]->turnEnd();
			turnIndex = (turnIndex + 1) % 2;
			players[turnIndex]->turnStart();
		}
	}

}

void Game::draw() {
	window.clear();

	window.draw(*gameField);
	window.draw(*players[0]);
	window.draw(*players[1]);

	window.display();
}
