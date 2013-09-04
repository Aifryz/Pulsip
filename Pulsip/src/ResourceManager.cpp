#include "../include/ResourceManager.h"

ResourceManager::ResourceManager()
{
	load();
}

bool ResourceManager::load()
{
	return 
		(
		loadTexture("player.png")
		);
}

const sf::Texture& ResourceManager::getTexture(std::string name)
{
	return m_textures[name];
}

const sf::Font& ResourceManager::getFont(std::string name)
{
	return m_fonts[name];
}

const sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string name)
{
	return m_soundbuffers[name];
}

bool ResourceManager::loadTexture(std::string name)
{
	sf::Texture txt;
	if(!txt.loadFromFile(name))
		return false;
	m_textures[name] = txt;
	return true;
}

bool ResourceManager::loadFont(std::string name)
{
	sf::Font font;
	if(!font.loadFromFile(name))
		return false;
	m_fonts[name] = font;
	return true;
}

bool ResourceManager::loadSoundBuffer(std::string name)
{
	sf::SoundBuffer buffer;
	if(!buffer.loadFromFile(name))
		return false;
	m_soundbuffers[name] = buffer;
	return true;
}
