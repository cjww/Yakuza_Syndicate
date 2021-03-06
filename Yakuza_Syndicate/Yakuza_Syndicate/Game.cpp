#include "Game.h"

Game::Game() :
	timePerFrame(sf::seconds(1.0f / 60.0f)),
	elapsedTime(sf::Time::Zero),
	window(sf::VideoMode::getFullscreenModes()[0], "Yakuza Syndicate", sf::Style::Fullscreen),
	serverAcceptThread(&Game::acceptThread, this),
	clientConnectThread(&Game::connectThread, this),
	processMessagesThread(&Game::processMessages, this)
{

	ResourceManager::newTexture("../res/katana_general.png", "GangMembers");
	ResourceManager::newTexture("../res/police_badge.png", "PolicePatrol");
	ResourceManager::newTexture("../res/Dojo_general.png", "Dojo");
	ResourceManager::newTexture("../res/Safe-House_general.png", "SafeHouse");
	ResourceManager::newTexture("../res/Bank.png", "Bank");
	ResourceManager::newTexture("../res/Police-Station.png", "PoliceStation");
	ResourceManager::newTexture("../res/tiles.png", "Tiles");
	ResourceManager::newTexture("../res/Hammer.png", "Hammer");
	ResourceManager::newTexture("../res/Dojo_Construct.png", "Dojo_Construct");
	ResourceManager::newSoundBuffer("../res/katana.wav", "Katana");
	ResourceManager::newSoundBuffer("../res/Hammer.wav", "Hammer");
	ResourceManager::newSoundBuffer("../res/coinSound.wav", "Coins");


	this->lastState = GameState::MENU;
	setState(GameState::MENU);

	gameField = new GameField(window);
	players[0] = new Player(gameField, Owner::PLAYER1, window);
	players[1] = new Player(gameField, Owner::PLAYER2, window);
	winner = -1;

	//Menu setup
	labelVis = {};
	labelVis.textFillColor = sf::Color::White;

	activeVis = {};
	activeVis.textOutlineThickness = 1;
	activeVis.textOutlineColor = sf::Color::White;

	inactiveVis = activeVis;
	inactiveVis.rectFillColor = sf::Color(50, 50, 50);
	inactiveVis.textFillColor = sf::Color(80, 80, 80);

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
	colors[10] = sf::Color(17, 213, 158);
	colors[11] = sf::Color(201, 181, 24);
	clrPlayer1 = 0;
	clrPlayer2 = 1;

	titleFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	titleText.setFont(titleFont);
	titleText.setString("Yakuza Syndicate");
	//titleText.setFillColor(sf::Color::Magenta);
	titleText.setPosition(window.getSize().x / 3, 200);
	titleText.setCharacterSize(80);
	titleText.setOutlineThickness(2);
	titleText.setOutlineColor(sf::Color::Black);

	menu.addChild(
		(playLocalBtn = new Button("Play Local", sf::Vector2f(window.getSize().x/3, 50), activeVis)),
		sf::Vector2f(window.getSize().x/3, 400));
	for (int i = 0; i < COLOR_COUNT; i++) {
		UIVisualSettings colorBtn;
		colorBtn.rectFillColor = colors[i];
		menu.addChild((colorBtns[i] = new Button(colorBtn)),
			sf::Vector2f(50 + 65 * (i % (COLOR_COUNT/2)), 375 + 65 * (i / (COLOR_COUNT/2))));
	}
	UIVisualSettings newVis = colorBtns[clrPlayer1]->getVisuals();
	newVis.rectOutlineThicknes = 5;
	newVis.rectOutlineColor = sf::Color::Black;
	colorBtns[clrPlayer1]->setVisuals(newVis);

	newVis = colorBtns[clrPlayer2]->getVisuals();
	newVis.rectOutlineThicknes = 5;
	newVis.rectOutlineColor = sf::Color::White;
	colorBtns[clrPlayer2]->setVisuals(newVis);

	
	menu.addChild(
		(playNetBtn = new Button("Play LAN", sf::Vector2f(window.getSize().x / 3, 50), activeVis)),
		sf::Vector2f(window.getSize().x / 3, 500));
	menu.addChild(
		(exitBtn = new Button("Exit", sf::Vector2f(window.getSize().x / 3, 50), activeVis)),
		sf::Vector2f(window.getSize().x / 3, 600));

	menuNet.addChild(
		(hostBtn = new Button("Host", sf::Vector2f(window.getSize().x/3, 50), activeVis)),
		sf::Vector2f(window.getSize().x/3, 400));
	hostBtn->addChild(
		(ipLabel = new Label("", labelVis)), sf::Vector2f(0, -100));
	menuNet.addChild(
		(joinBtn = new Button("Join", sf::Vector2f(window.getSize().x / 3, 50), activeVis)),
		sf::Vector2f(window.getSize().x / 3, 500));
	menuNet.addChild((addressInput = new TextField("127.0.0.1", sf::Vector2f(window.getSize().x / 3, 50), activeVis)),
		sf::Vector2f(window.getSize().x / 3, 600));
	addressInput->setVisuals(inactiveVis);

	menuNet.addChild(
		(backBtn = new Button("Back", sf::Vector2f(window.getSize().x / 3, 50), activeVis)),
		sf::Vector2f(window.getSize().x / 3, 700));
	
	gameMenuBtn = new Button("Game Menu", sf::Vector2f(window.getSize().x / 3, 50), activeVis);
	gameMenuBtn->setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y - 75));

	resumeBtn = new Button("Resume", sf::Vector2f(window.getSize().x / 3, 50), activeVis);
	resumeBtn->setPosition(sf::Vector2f(window.getSize().x / 3, 400));
	gameMenu.addChild(
		(mainMenuBtn = new Button("Main Menu", sf::Vector2f(window.getSize().x / 3, 50), activeVis)),
		sf::Vector2f(window.getSize().x / 3, 500));
	gameMenu.addChild(
		(gameMenuExitBtn = new Button("Exit Game", sf::Vector2f(window.getSize().x / 3, 50), activeVis)),
		sf::Vector2f(window.getSize().x / 3, 600));

	winnerFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	winnerText.setString("player...");
	winnerText.setFont(winnerFont);
	winnerText.setPosition(window.getSize().x / 3, 400);

	music.openFromFile("../res/music.wav");
	music.setLoop(true);
	music.setVolume(50);
	
	sf::Image cursorImage;
	cursorImage.loadFromFile("../res/Cursor.png");
	cur.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
	window.setMouseCursor(cur);

	turnIndex = 0;
	while (window.isOpen()) {
		handleEvents();
		update();
		draw();
	}

	Message msg;
	msg.type = MessageType::DISCONNECT;
	NetworkManager::send(msg);

	NetworkManager::close();

	clientConnectThread.terminate();
	serverAcceptThread.terminate();
	processMessagesThread.terminate();

}

Game::~Game() {
	delete gameField;
	delete players[0];
	delete players[1];
	delete gameMenuBtn;
	delete resumeBtn;
}

void Game::handleEvents() {
	sf::Event e;
	while (window.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::Closed:
			window.close();
			break;
		}
		if (state == GameState::MENU || state == GameState::MENU_NET || state == GameState::MENU_NET_WAIT) {
			handleEventsMenu(e);
		}
		else if (state == GameState::GAME_LOCAL) {
			handleEventsLocalGame(e);
			if (e.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
				if (gameMenuBtn->contains(mousePos))
				{
					setState(GameState::GAME_MENU);
				}
			}
		}
		else if (state == GameState::GAME_NET) {
			if ((NetworkManager::isHost() && turnIndex == 0) || (!NetworkManager::isHost() && turnIndex == 1)) {
				handleEventsLocalGame(e);
			}
			if (e.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
				if (gameMenuBtn->contains(mousePos))
				{
					setState(GameState::GAME_MENU);
				}
			}
		}
		else if(state == GameState::GAME_MENU) {
			if (e.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
				if (resumeBtn->contains(mousePos) && winner == -1)
				{
					setState(lastState);
				}
				else if (mainMenuBtn->contains(mousePos))
				{
					setState(GameState::MENU);
					Message msg;
					msg.type = MessageType::DISCONNECT;
					NetworkManager::send(msg);
					processMessagesThread.terminate();

					music.stop();

				}
				else if (gameMenuExitBtn->contains(mousePos))
				{
					window.close();
				}
			}
		}
	}

}

void Game::update() {
	elapsedTime += clock.restart();
	while (elapsedTime > timePerFrame) {
		window.setTitle("FPS: " + std::to_string(1 / elapsedTime.asSeconds()));
		elapsedTime -= timePerFrame;

		if (this->state == GameState::MENU_NET && this->lastState == GameState::MENU_NET_WAIT) {
			menuNet.setVisuals(activeVis);
			addressInput->setVisuals(inactiveVis);
			addressInput->setFocused(false);
			ipLabel->setVisuals(labelVis);
			this->lastState = this->state;
		}
		if (this->state == GameState::MENU && this->lastState == GameState::MENU_NET) {
			ipLabel->setString("");
			this->lastState = this->state;
		}
		if (state == GameState::GAME_NET && lastState == GameState::MENU_NET_WAIT) {
			menuNet.setVisuals(activeVis);
			addressInput->setVisuals(inactiveVis);
			addressInput->setFocused(false);
			ipLabel->setVisuals(labelVis);
			players[turnIndex]->turnStart();
			music.stop();
			music.play();
			this->lastState = this->state;
		}
		else if (state == GameState::GAME_LOCAL || state == GameState::GAME_NET) {
			updateGame();
		}
	}
}

void Game::draw() {

	window.clear(sf::Color(92, 86, 43));
	if (state == GameState::MENU || state == GameState::MENU_NET || state == GameState::MENU_NET_WAIT) {
		drawMenu();
	}
	else if (state == GameState::GAME_LOCAL || state == GameState::GAME_NET || state == GameState::GAME_MENU) {
		drawGame();
	}

	window.display();
}

void Game::setState(GameState state) {
	this->lastState = this->state;
	this->state = state;
}

void Game::handleEventsMenu(const sf::Event& e) {
	if (e.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
		if (state == GameState::MENU) {
			if (playLocalBtn->contains(mousePos)) {
				setState(GameState::GAME_LOCAL);
				players[0]->setColor(colors[clrPlayer1]);
				players[1]->setColor(colors[clrPlayer2]);

				players[turnIndex]->turnStart();
				music.stop();
				music.play();
			}
			else if (playNetBtn->contains(mousePos)) {
				players[0]->setColor(colors[clrPlayer1]);
				setState(GameState::MENU_NET);
				//Read file
				std::ifstream infile("../res/last_ip.txt");
				if (infile) {
					std::string ip;
					infile >> ip;
					addressInput->setText(ip);
				}
				infile.close();

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
		else if (state == GameState::MENU_NET) {
			if (backBtn->contains(mousePos)) {
				addressInput->setFocused(false);
				addressInput->setVisuals(inactiveVis);
				setState(GameState::MENU);
			}
			else if (joinBtn->contains(mousePos)) {
				//Write file
				std::ofstream outfile("../res/last_ip.txt");
				if (outfile) {
					outfile << addressInput->getText();
				}
				outfile.close();

				initNetworkgame(false);
			}
			else if (addressInput->contains(mousePos)) {
				addressInput->setFocused(true);
				addressInput->setVisuals(activeVis);
			}
			else if (hostBtn->contains(mousePos)) {
				initNetworkgame(true);
			}
			else {
				addressInput->setFocused(false);
				addressInput->setVisuals(inactiveVis);
			}
		}
		else if (state == GameState::MENU_NET_WAIT) {
			if (backBtn->contains(mousePos)) {
				setState(GameState::MENU_NET);
				menuNet.setVisuals(activeVis);
				addressInput->setFocused(false);
				addressInput->setVisuals(inactiveVis);
				ipLabel->setVisuals(activeVis);
				NetworkManager::close();
			}
		}
	}
	else if (e.type == sf::Event::TextEntered) {
		addressInput->handleInput(e);
	}

}

void Game::drawMenu() {
	if (state == GameState::MENU) {
		window.draw(menu);
		window.draw(titleText);
	}
	else {
		window.draw(menuNet);
	}

}

void Game::handleEventsLocalGame(const sf::Event& e) {
	if (e.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
		players[turnIndex]->mousePressed(mousePos, e.mouseButton.button);
	}
	else if (e.type == sf::Event::KeyPressed)
	{
		players[turnIndex]->keyPressed(e.key.code);
	}
}

void Game::updateGame() {
	players[turnIndex]->update();
	gameField->updateAnimations();
	if (players[turnIndex]->wantsToEndTurn()) {
		if (NetworkManager::isOpen()) { //if connected or hosting
			if ((NetworkManager::isHost() && (Owner)turnIndex == Owner::PLAYER1) ||
				(!NetworkManager::isHost() && (Owner)turnIndex == Owner::PLAYER2)) 
			{
				Message msg;
				msg.type = MessageType::END_TURN;
				NetworkManager::send(msg);
			}
		}
		players[turnIndex]->checkFight(players[(turnIndex + 1) % 2]);
		gameField->movePolice();

		players[turnIndex]->turnEnd();
		if (players[turnIndex]->checkIfWin())
		{
			winner = turnIndex;
			state = GameState::GAME_MENU;
		}
		turnIndex = (turnIndex + 1) % 2;
		players[turnIndex]->turnStart();
	}
}

void Game::drawGame() {
	window.draw(*gameField);
	players[0]->drawTerritory(window);
	players[1]->drawTerritory(window);
	window.draw(*players[0]);
	window.draw(*players[1]);
	window.draw(*gameMenuBtn);
	if (state == GameState::GAME_MENU)
	{
		window.draw(gameMenu);
		if (winner != -1)
		{
			winnerText.setFillColor(players[winner]->getColor());
			winnerText.setString("Player " + std::to_string(winner + 1) + " wins!");
			window.draw(winnerText);
		}
		else
		{
			window.draw(*resumeBtn);
		}
	}
}

void Game::acceptThread() {

	auto status = NetworkManager::accept();
	if (status == sf::Socket::Done) {
		ipLabel->setString("");
		setState(GameState::GAME_NET);
		Message msg;
		if (NetworkManager::recv(msg) != sf::Socket::Done) {
			std::cout << "Failed to recv color" << std::endl;
		}
		else {
			if (colors[clrPlayer1] == msg.color) {
				clrPlayer1 = (clrPlayer1 + 1) % COLOR_COUNT;
			}
			players[1]->setColor(msg.color);
			turnIndex = 0;
		}
		players[0]->setColor(colors[clrPlayer1]);
		msg.color = colors[clrPlayer1];
		if (NetworkManager::send(msg) != sf::Socket::Done) {
			std::cout << "Failed to send" << std::endl;
		}
		processMessagesThread.launch();
	}
	else if (status == sf::Socket::Error) {
		ipLabel->setString("");
	}
	else {
		ipLabel->setString("Failed to accept client");
		setState(GameState::MENU_NET);
	}
}

void Game::connectThread() {
	std::string ip = addressInput->getText();
	if (NetworkManager::connect(ip, 5490) != sf::Socket::Done) {
		ipLabel->setString("Failed to connect");
		setState(GameState::MENU_NET);
	}
	else {
		players[1]->setColor(colors[clrPlayer1]);
		setState(GameState::GAME_NET);
		std::cout << "Connected!" << std::endl;
		//Send Color
		Message msg;
		msg.type = MessageType::COLOR_CHANGED;
		msg.color = colors[clrPlayer1];
		if (NetworkManager::send(msg) != sf::Socket::Done) {
			std::cout << "Failed to send color" << std::endl;
		}

		if (NetworkManager::recv(msg) != sf::Socket::Done) {
			std::cout << "Failed to recv color" << std::endl;
		}
		else {
			players[0]->setColor(msg.color);
		}
		processMessagesThread.launch();
	}
}

void Game::processMessages() {
	Message msg;
	do {
		NetworkManager::recv(msg);
		switch (msg.type) {
		case MessageType::DISCONNECT:
			ipLabel->setString("Player disconnected");
			setState(GameState::MENU_NET);
			music.stop();
			break;
		default:
			players[turnIndex]->proccessMessage(msg);
			break;
		}
	} while (msg.type != MessageType::DISCONNECT);

}

void Game::initNetworkgame(bool isHost) {
	setState(GameState::MENU_NET_WAIT);
	menuNet.setVisuals(inactiveVis);
	backBtn->setVisuals(activeVis);
	ipLabel->setVisuals(labelVis);
	if (isHost) {
		try{
			NetworkManager::listen(5490);

			ipLabel->setString("Server located at : " + sf::IpAddress::getLocalAddress().toString());

			serverAcceptThread.launch();
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
			setState(GameState::MENU);
		}
	}
	else {
		
		clientConnectThread.launch();
	}
}
