#include "../include/Tile.h"

Tile::Tile(int subtype, int x, int y)
{
	m_type = subtype;
	m_position = sf::Vector2i(x,y);
	m_size = sf::Vector2i(32,32);
}

void Tile::tick(sf::Time ticktime)
{

}

sf::Vector2i Tile::getSize() const
{
	return sf::Vector2i(32,32);
}

sf::Vector2i Tile::getPosition() const
{
	return m_position;
}

int Tile::getType() const
{
	return m_type;
}

bool Tile::isCollideable() const
{
	switch (m_type)
	{
        case(1):
        case(3):
            return true;
        default:
            return false;
	}
}
