#include "Game.h"

Game::Game() : m_window(sf::VideoMode(1000, 600), "Yakuza Syndicate") {

	while (m_window.isOpen()) {
		handleEvents();
		update();
		draw();
	}
}

Game::~Game() {

}

void Game::handleEvents() {
	sf::Event e;
	while (m_window.pollEvent(e)) {
		switch(e.type){
		case sf::Event::Closed:
			m_window.close();
			break;
		}

	}
}

void Game::update() {
	float elapsedTime = m_clock.restart().asSeconds();
	
	m_window.setTitle(std::to_string(1 / elapsedTime));
}

void Game::draw() {
	m_window.clear();


	m_window.display();
}
