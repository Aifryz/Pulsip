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
        case(16):
        case(17):
            return true;
        default:
            return false;
	}
}
bool Tile::intersects(sf::Vector2i p1, sf::Vector2i p2) const
{
	int valarr[4];
	sf::Vector2i parr[4] = 
	{
		getPosition(),
		sf::Vector2i(getPosition().x+getSize().x , getPosition().y),
		sf::Vector2i(getPosition().x             , getPosition().y+getSize().y),
		getPosition()+getSize()
	};
	for (int i = 0; i < 4; i++)
	{
		int val = (p2.y-p1.y)*parr[i].x + (p1.x-p2.x)*parr[i].y + (p2.x*p1.y-p1.x*p2.y);
		if(val<0)
			valarr[i]=0;
		else if(val == 0)
			valarr[i] = 1;
		else if(val > 0)
			valarr[i] = 3;
	}
	if(valarr[0] == valarr[1] && valarr[1] == valarr[2] && valarr[2] == valarr[3])
		return false;
	return true;
}
