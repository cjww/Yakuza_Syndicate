#include "Game.h"

Game::Game() : window(sf::VideoMode(1000, 600), "Yakuza Syndicate"),
	timePerFrame(sf::seconds(1.0f /60.0f)),
	elapsedTime(sf::Time::Zero) {

	turn = 0;
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
			players[turn].mousePressed(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));
			break;
		}

	}
}

void Game::update() {
	elapsedTime += clock.restart();
	while (elapsedTime > timePerFrame) {
		window.setTitle("FPS: " + std::to_string(1 / elapsedTime.asSeconds()));
		elapsedTime -= timePerFrame;
	
		players[turn].update();
		if (players[turn].getEndTurn()) {
			players[turn].setEndTurn(false);
			turn = (turn + 1) % 2;
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
