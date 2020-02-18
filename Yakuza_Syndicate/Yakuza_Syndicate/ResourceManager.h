#pragma once
#include <SFML/Graphics.hpp>

class ResourceManager {
private:
	static std::map<std::string, sf::Texture> textures;
public:
	static sf::Texture* newTexture(const std::string& filename, const std::string& name);
	static sf::Texture* getTexture(const std::string& name);


};
