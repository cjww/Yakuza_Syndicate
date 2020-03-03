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
	ResourceManager::newTexture("../res/tiles.png", "Tiles");

	state = GameState::MENU;

	gameField = new GameField(window);
	players[0] = new Player(gameField, Owner::PLAYER1, window);
	players[1] = new Player(gameField, Owner::PLAYER2, window);


	colors[0] = sf::Color::Green;
	colors[1] = sf::Color::Red;
	colors[2] = sf::Color::Blue;
	colors[3] = sf::Color::Magenta;
	colors[4] = sf::Color::Yellow;
	colors[5] = sf::Color::White;

	colors[6] = sf::Color::Black;
	colors[7] = sf::Color::Cyan;
	colors[8] = sf::Color(46, 143, 59);
	colors[9] = sf::Color(50, 75, 143);
	colors[10] = sf::Color(166, 5, 5);
	colors[11] = sf::Color(201, 181, 24);

	menu.addChild(
		(playLocalBtn = new Button("Play Local", sf::Vector2f(window.getSize().x/3, 50))),
		sf::Vector2f(window.getSize().x/3, 400));

	clrPlayer1 = 0;
	clrPlayer2 = 1;
	for (int i = 0; i < COLOR_COUNT; i++) {
		UIVisualSettings colorBtn;
		colorBtn.rectFillColor = colors[i];
		menu.addChild((colorBtns[i] = new Button(colorBtn)),
			sf::Vector2f(50 + 65 * (i % (COLOR_COUNT/2)), 375 + 65 * (i / (COLOR_COUNT/2))));
	}

	menu.addChild(
		(playNetBtn = new Button("Play LAN", sf::Vector2f(window.getSize().x / 3, 50))),
		sf::Vector2f(window.getSize().x / 3, 500));

	menu.addChild(
		(exitBtn = new Button("Exit", sf::Vector2f(window.getSize().x / 3, 50))),
		sf::Vector2f(window.getSize().x / 3, 600));


	
	turnIndex = 0;
	
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
			sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
			if (state == GameState::MENU) {
				if (playLocalBtn->contains(mousePos)) {
					state = GameState::GAME_LOCAL;
					players[0]->setColor(colors[clrPlayer1]);
					players[1]->setColor(colors[clrPlayer2]);

					players[turnIndex]->turnStart();
				}
				else if (playNetBtn->contains(mousePos)) {
					state = GameState::GAME_NET;
					players[turnIndex]->turnStart();
				}
				else if (exitBtn->contains(mousePos)) {
					window.close();
				}

				for (int i = 0; i < COLOR_COUNT; i++) {
					if (colorBtns[i]->contains(mousePos)) {

						if (e.mouseButton.button == sf::Mouse::Button::Left) {
							if (clrPlayer2 != i) {
								UIVisualSettings oldVis = colorBtns[clrPlayer1]->getVisuals();
								oldVis.rectOutlineThicknes = 0;
								UIVisualSettings newVis = colorBtns[i]->getVisuals();
								newVis.rectOutlineThicknes = 5;
								newVis.rectOutlineColor = sf::Color::Black;
								colorBtns[clrPlayer1]->setVisuals(oldVis);
								clrPlayer1 = i;
								colorBtns[i]->setVisuals(newVis);
							}
						}
						else {
							if (clrPlayer1 != i) {
								UIVisualSettings oldVis = colorBtns[clrPlayer2]->getVisuals();
								oldVis.rectOutlineThicknes = 0;
								UIVisualSettings newVis = colorBtns[i]->getVisuals();
								newVis.rectOutlineThicknes = 5;
								newVis.rectOutlineColor = sf::Color::White;
								colorBtns[clrPlayer2]->setVisuals(oldVis);
								clrPlayer2 = i;
								colorBtns[i]->setVisuals(newVis);
							}
						}
					}
				}

			}
			else if (state == GameState::GAME_LOCAL) {
				players[turnIndex]->mousePressed(mousePos, e.mouseButton.button);
			}
			break;
		}

	}
}

void Game::update() {
	elapsedTime += clock.restart();
	while (elapsedTime > timePerFrame) {
		window.setTitle("FPS: " + std::to_string(1 / elapsedTime.asSeconds()));
		elapsedTime -= timePerFrame;

		if (state == GameState::MENU) {
			
		}
		else if (state == GameState::GAME_LOCAL) {
			players[turnIndex]->update();
			if (players[turnIndex]->wantsToEndTurn()) {
				players[turnIndex]->turnEnd();
				turnIndex = (turnIndex + 1) % 2;
				players[turnIndex]->turnStart();
			}
		
		}
	}

}

void Game::draw() {

	window.clear(sf::Color(92, 86, 43));
	if (state == GameState::MENU) {
		window.draw(menu);
	}
	else if (state == GameState::GAME_LOCAL) {
		window.draw(*gameField);
		window.draw(*players[0]);
		window.draw(*players[1]);
	}


	window.display();
}
