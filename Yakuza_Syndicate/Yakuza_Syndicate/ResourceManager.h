#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class ResourceManager {
private:
	static std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::SoundBuffer> soundBuffers;
public:
	static sf::Texture& newTexture(const std::string& filename, const std::string& name);
	static sf::Texture& getTexture(const std::string& name);

	static sf::SoundBuffer& newSoundBuffer(const std::string& filename, const std::string& name);
	static sf::SoundBuffer& getSoundBuffer(const std::string& name);


};
