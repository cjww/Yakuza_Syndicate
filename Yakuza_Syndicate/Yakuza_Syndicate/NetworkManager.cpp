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
	sf::Socket::Status status = sf::Socket::Status::NotReady;
	if (open) {
		status = socket.send(&msg, sizeof(msg));
	}
	return status;
}

sf::Socket::Status NetworkManager::recv(Message& msg) {
	sf::Socket::Status status = sf::Socket::Status::NotReady;
	if (open) {
		size_t recvSize;
		status = socket.receive(&msg, sizeof(msg), recvSize);
	}
	return status;
}

bool NetworkManager::isHost() {
	return host;
}

bool NetworkManager::isOpen() {
	return open;
}
