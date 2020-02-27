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
	players[1].setColor(sf::Color::Magenta);

	turnIndex = 0;
	players[turnIndex].turnStart();

	UIVisualSettings uiVis = {};
	uiVis.rectFillColor = sf::Color::Blue;
	uiVis.textOutlineColor = sf::Color::Magenta;
	uiVis.textOutlineThickness = 1;

	elem.addChild(new Button("Press me", sf::Vector2f(400, 100), uiVis), sf::Vector2f(50, 100))
		->addChild(new Label("value"), sf::Vector2f(500, 0));
	uiVis.rectFillColor = sf::Color::Red;
	elem.addChild(new Button(uiVis));
	elem.addChild(new Button(new Image(*ResourceManager::getTexture("Dojo"))), sf::Vector2f(100, 500));

	
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

	window.draw(elem);

	window.display();
}
