#include "Player.h"
#include "GameField.h"

#include "UI.h"
#include "NetworkManager.h"

enum class GameState {
	MENU,		//Main Menu
	MENU_NET,	//Menu for hosting or joining network
	MENU_NET_WAIT,
	GAME_LOCAL, //Game on local comp
	GAME_NET	//Game over network
};

class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time timePerFrame;
	
	GameState lastState;
	GameState state;

	//Game states
	GameField* gameField;
	
	Player* players[2];
	int turnIndex;

	sf::Thread serverAcceptThread;
	sf::Thread clientConnectThread;
	void acceptThread();
	void connectThread();

	//Menu states
	Pane menu;
	Button* playLocalBtn;
	Button* playNetBtn;
	Button* exitBtn;

	static const int COLOR_COUNT = 12;
	int clrPlayer1;
	int clrPlayer2;
	Button* colorBtns[COLOR_COUNT];
	sf::Color colors[COLOR_COUNT];

	//Network menu
	UIVisualSettings activeVis;
	UIVisualSettings inactiveVis;
	UIVisualSettings labelVis;
	Pane menuNet;
	Button* hostBtn;
	Label* ipLabel;
	Button* joinBtn;
	//TODO TextField* address
	Button* backBtn;

public:
	Game();
	virtual ~Game();

	void handleEvents();
	void update();
	void draw();

	void setState(GameState state);

	void handleEventsMenu(const sf::Event& e);
	void drawMenu();
	
	void handleEventsLocalGame(const sf::Event& e);
	void updateGame();
	void drawGame();

	void initNetworkgame(bool isHost);

};