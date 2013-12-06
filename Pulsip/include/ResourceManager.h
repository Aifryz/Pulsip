#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class ResourceManager
{
    public:
        ResourceManager();

        const sf::Texture& getTexture(std::string name);
        const sf::Font& getFont(std::string name);
        const sf::SoundBuffer& getSoundBuffer(std::string name);
    private:
        bool m_loadTexture(std::string name);
        bool m_loadFont(std::string name);
        bool m_loadSoundBuffer(std::string name);
        std::map<std::string,sf::Texture> m_textures;
        std::map<std::string,sf::Font> m_fonts;
        std::map<std::string,sf::SoundBuffer> m_soundbuffers;
};

#endif
