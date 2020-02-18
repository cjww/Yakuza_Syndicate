#include "ResourceManager.h"
std::map<std::string, sf::Texture> ResourceManager::textures;

sf::Texture* ResourceManager::newTexture(const std::string& filename, const std::string& name) {
	if (textures.find(name) != textures.end()) {
		throw std::runtime_error("Name already exists!");
	}
	else {
		textures[name].loadFromFile(filename);
	}

	return &textures[name];
}

sf::Texture* ResourceManager::getTexture(const std::string& name) {
	if (textures.find(name) == textures.end()) {
		throw std::runtime_error("Found no name " + name);
	}
	return &textures[name];
}

