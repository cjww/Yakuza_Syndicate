#include "Game.h"

Game::Game() : 
	timePerFrame(sf::seconds(1.0f /60.0f)),
	elapsedTime(sf::Time::Zero),
	gameField(window), 
	players{ Player(&gameField), Player(&gameField) },
	window(sf::VideoMode::getFullscreenModes()[0], "Yakuza Syndicate", sf::Style::Fullscreen)
{

	turnIndex = 0;
	players[0].setColor(sf::Color::Red);
	players[1].setColor(sf::Color::Green);


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
			players[turnIndex].mousePressed(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));
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
		if (players[turnIndex].getEndTurn()) {
			players[turnIndex].setEndTurn(false);
			turnIndex = (turnIndex + 1) % 2;
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
