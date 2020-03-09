#include "NetworkManager.h"

sf::TcpListener NetworkManager::listener;
sf::TcpSocket NetworkManager::socket;
bool NetworkManager::host;
bool NetworkManager::open = false;

void NetworkManager::listen(unsigned short port) {
	host = true;
	if (listener.listen(port) != sf::Socket::Done) {
		throw std::runtime_error("Failed to listen on port " + port);
	}
}

sf::Socket::Status NetworkManager::accept() {
	host = true;
	auto status = listener.accept(socket);
	if (status == sf::Socket::Done) {
		open = true;
	}
	return status;
}

sf::Socket::Status NetworkManager::connect(const std::string& ip, unsigned short port) {
	host = false;
	auto status = socket.connect(ip, port);
	if (status == sf::Socket::Done) {
		open = true;
	}
	return status;
}

void NetworkManager::close() {
	if (host) {
		listener.close();
	}
	else {
		socket.disconnect();
	}
	open = false;
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

bool NetworkManager::isHost() {
	return host;
}

bool NetworkManager::isOpen() {
	return open;
}
