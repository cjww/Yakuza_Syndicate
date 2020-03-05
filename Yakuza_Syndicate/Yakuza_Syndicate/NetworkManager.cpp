#include "NetworkManager.h"

sf::TcpListener NetworkManager::listener;
sf::TcpSocket NetworkManager::socket;
bool NetworkManager::isHost;

void NetworkManager::listen(unsigned short port) {
	isHost = true;
	if (listener.listen(port) != sf::Socket::Done) {
		throw std::runtime_error("Failed to listen on port " + port);
	}
}

sf::Socket::Status NetworkManager::accept() {
	isHost = true;
	return listener.accept(socket);
}

sf::Socket::Status NetworkManager::connect(const std::string& ip, unsigned short port) {
	isHost = false;
	return socket.connect(ip, port);
}

void NetworkManager::close() {
	if (isHost) {
		listener.close();
	}
	else {
		socket.disconnect();
	}
}

sf::Socket::Status NetworkManager::send(Message& msg) {
	sf::Packet p;
	p.append(&msg, sizeof(msg));
	return socket.send(p);
}

sf::Socket::Status NetworkManager::recv(Message& msg) {
	sf::Packet p;
	sf::Socket::Status status = socket.receive(p);
	if (status == sf::Socket::Done) {
		msg = *(Message*)p.getData();
	}
	return status;
}
