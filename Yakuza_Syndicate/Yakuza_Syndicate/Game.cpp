#include "Game.h"

Game::Game() : 
	timePerFrame(sf::seconds(1.0f /60.0f)),
	elapsedTime(sf::Time::Zero),
	gameField(window), 
	players{ Player(&gameField, 0), Player(&gameField, 1) },
	//window(sf::VideoMode(1000, 600), "Yakuza Syndicate")
	window(sf::VideoMode::getFullscreenModes()[0], "Yakuza Syndicate", sf::Style::Fullscreen)
{

	ResourceManager::newTexture("../res/katana_general.png", "GangMembers");

	players[0].setColor(sf::Color::Cyan);
	players[1].setColor(sf::Color::Red);

	turnIndex = 0;
	players[turnIndex].turnStart();
	
	while (window.isOpen()) {
		handleEvents();
		update();
		draw();
	}
}

Game::~Game() {

}

void Game::handleEvents() {
	sf::Event e;
	while (window.pollEvent(e)) {
		switch(e.type){
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
				players[turnIndex].mousePressed(sf::Vector2f(e.mouseButton.x, e.mouseButton.y), e.mouseButton.button);
			break;
		}

	}
}

void Game::update() {
	elapsedTime += clock.restart();
	while (elapsedTime > timePerFrame) {
		window.setTitle("FPS: " + std::to_string(1 / elapsedTime.asSeconds()));
		elapsedTime -= timePerFrame;
	
		players[turnIndex].update();
		if (players[turnIndex].wantsToEndTurn()) {
			players[turnIndex].turnEnd();
			turnIndex = (turnIndex + 1) % 2;
			players[turnIndex].turnStart();
		}
	}

}

void Game::draw() {
	window.clear();

	window.draw(gameField);
	window.draw(players[0]);
	window.draw(players[1]);

	window.display();
}
