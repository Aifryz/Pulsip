#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <map>
#include <string>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
class ResourceManager
{
public:
	ResourceManager();
	
	bool load();

	const sf::Texture& getTexture(std::string name);
	const sf::Font& getFont(std::string name);
	const sf::SoundBuffer& getSoundBuffer(std::string name);
private:
	bool loadTexture(std::string name);
	bool loadFont(std::string name);
	bool loadSoundBuffer(std::string name);
	std::map<std::string,sf::Texture> m_textures;
	std::map<std::string,sf::Font> m_fonts;
	std::map<std::string,sf::SoundBuffer> m_soundbuffers;

};

#endif