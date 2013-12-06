#include "../include/ResourceManager.h"

ResourceManager::ResourceManager()
{
}

const sf::Texture& ResourceManager::getTexture(std::string name)
{
	std::map<std::string,sf::Texture>::iterator it = m_textures.find(name);
	if(it != m_textures.end())
		return it->second;
	m_loadTexture(name);//ignoring any loading errors <-badbadbad, although sfml will write error on console
	return m_textures[name];
}

const sf::Font& ResourceManager::getFont(std::string name)
{
	std::map<std::string,sf::Font>::iterator it = m_fonts.find(name);
	if(it != m_fonts.end())
		return it->second;
	m_loadFont(name);//ignoring any loading errors <-badbadbad, although sfml will write error on console
	return m_fonts[name];
}

const sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string name)
{
	std::map<std::string,sf::SoundBuffer>::iterator it = m_soundbuffers.find(name);
	if(it != m_soundbuffers.end())
		return it->second;
	m_loadTexture(name);//ignoring any loading errors <-badbadbad, although sfml will write error on console
	return m_soundbuffers[name];
}

bool ResourceManager::m_loadTexture(std::string name)
{
	sf::Texture txt;
	if(!txt.loadFromFile(name))
		return false;
	m_textures[name] = txt;
	return true;
}

bool ResourceManager::m_loadFont(std::string name)
{
	sf::Font font;
	if(!font.loadFromFile(name))
		return false;
	m_fonts[name] = font;
	return true;
}

bool ResourceManager::m_loadSoundBuffer(std::string name)
{
	sf::SoundBuffer buffer;
	if(!buffer.loadFromFile(name))
		return false;
	m_soundbuffers[name] = buffer;
	return true;
}
