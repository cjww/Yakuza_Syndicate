#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
enum class MessageType {
	GANGMEMBER_MOVED,
	DOJO_BUILT,
	COLOR_CHANGED
};

struct Message {
	MessageType type;
	sf::Color color;
	sf::Vector2f vec1;
	sf::Vector2f vec2;
};

class NetworkManager {
private:
	static sf::TcpListener listener;
	static sf::TcpSocket socket;
	static bool isHost;
public:
	static void listen(unsigned short port);
	static sf::Socket::Status accept();
	static sf::Socket::Status connect(const std::string& ip, unsigned short port);
	static void close();

	static sf::Socket::Status send(Message& msg);
	static sf::Socket::Status recv(Message& msg);

};