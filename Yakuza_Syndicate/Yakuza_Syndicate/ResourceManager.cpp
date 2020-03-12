#include "ResourceManager.h"
std::map<std::string, sf::Texture> ResourceManager::textures;
std::map<std::string, sf::SoundBuffer> ResourceManager::soundBuffers;


sf::Texture& ResourceManager::newTexture(const std::string& filename, const std::string& name) {
	if (textures.find(name) != textures.end()) {
		throw std::runtime_error("Name already exists!");
	}
	else {
		textures[name].loadFromFile(filename);
	}

	return textures[name];
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
	if (textures.find(name) == textures.end()) {
		throw std::runtime_error("Found no name " + name);
	}
	return textures[name];
}

sf::SoundBuffer& ResourceManager::newSoundBuffer(const std::string& filename, const std::string& name) {
	if (soundBuffers.find(name) != soundBuffers.end()) {
		throw std::runtime_error("Name already exists!");
	}
	else {
		soundBuffers[name].loadFromFile(filename);
	}

	return soundBuffers[name];
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name) {
	if (soundBuffers.find(name) == soundBuffers.end()) {
		throw std::runtime_error("Found no name " + name);
	}
	return soundBuffers[name];
}

