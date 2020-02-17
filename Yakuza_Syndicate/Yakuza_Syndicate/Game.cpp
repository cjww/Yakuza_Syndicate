#include "Game.h"

Game::Game() : window(sf::VideoMode(1000, 600), "Yakuza Syndicate"),
	timePerFrame(sf::seconds(1.0f /60.0f)),
	elapsedTime(sf::Time::Zero) {

	turn = 0;

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
		}

	}
}

void Game::update() {
	elapsedTime += clock.restart();
	while (elapsedTime > timePerFrame) {
		window.setTitle("FPS: " + std::to_string(1 / elapsedTime.asSeconds()));
		elapsedTime -= timePerFrame;
	
		
	}

}

void Game::draw() {
	window.clear();


	window.display();
}
