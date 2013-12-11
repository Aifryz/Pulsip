#include"../include/TileMap.h"
#include<iostream>
TileMap::TileMap(sf::Texture* texture, unsigned int tilesize):
	m_texture(texture),
	m_tilesize(tilesize)
{}
void TileMap::load(std::string name)
{
	sf::Image map;
	map.loadFromFile(name);
	m_size = map.getSize();
	m_sectorsAmount = m_size / 16U;
	if(m_size.x %16 !=0)
		m_sectorsAmount.x++;
	if(m_size.y %16 !=0)
		m_sectorsAmount.y++;;

	sectors.resize(m_sectorsAmount.x * m_sectorsAmount.y);

	for(unsigned int y=0;y<m_sectorsAmount.y;y++)
	{
		for(unsigned int x=0;x<m_sectorsAmount.x;x++)
		{
			sf::Image dest;
			dest.create(16,16);
			dest.copy(map,0,0,sf::IntRect(x*16,y*16,16,16));
			sectors[y*m_sectorsAmount.y+x] = Sector(dest ,(x*16*m_tilesize) ,(y*16*m_tilesize),m_tilesize, m_texture);
		}
	}
}
Tile TileMap::getTileAt(int x, int y) const
{
	if(x>m_size.x || y>m_size.y)
		return Tile(0,0,0);
	
	int secx = x/16;
	int secy = y/16;
	
	return sectors[secy*m_sectorsAmount.y+secx].getTileAt(x,y);
	
}
void TileMap::setTile(Tile tile)
{
	
	int x = tile.getPosition().x/m_tilesize;
	int y = tile.getPosition().y/m_tilesize;
	if(x>m_size.x || y>m_size.y)
		return;
	int secx = x/16;
	int secy = y/16;
	sectors[secy*m_sectorsAmount.y+secx].setTile(tile);
}

sf::Vector2u TileMap::getSectorsAmount() const
{
	return m_sectorsAmount;
}
sf::Vector2u TileMap::getSize() const
{
	return m_size;
}

std::vector<Tile> TileMap::getCollidingWith(GameObject*object)const
{
	sf::IntRect rect = static_cast<sf::IntRect>( object->getColRect() );
	return getCollidingWith(rect);
}
std::vector<Tile> TileMap::getCollidingWith(sf::IntRect rect) const
{
	std::vector<Tile> returntiles;

	sf::Vector2i NW((rect.left)/m_tilesize           ,(rect.top)/m_tilesize);
	sf::Vector2i SE((rect.left+rect.width)/m_tilesize    ,(rect.top+rect.height)/m_tilesize);
		for (int y = NW.y; y <= SE.y; y++)
		{
			for (int x = NW.x; x <= SE.x; x++)
			{
				Tile get = getTileAt(x,y);

				if(get.isCollideable())
					returntiles.push_back(get);
			}
		}
	return returntiles;
}
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//calculate sectors to draw
	sf::Vector2i pos = static_cast<sf::Vector2i>(target.getView().getCenter() - target.getView().getSize()/2.f);
	sf::Vector2i  size = static_cast<sf::Vector2i>(target.getView().getSize());
	int left = (pos.x)/static_cast<int>(16*m_tilesize);
	int top = (pos.y)/static_cast<int>(16*m_tilesize);
	int right = (pos.x +size.x)/static_cast<int>(16*m_tilesize) +1;
	int bottom = (pos.y + size.y)/static_cast<int>(16*m_tilesize) +1;
	//just to be sure
	if(top < 0)
		top = 0;
	if(left < 0)
		left = 0;
	
	if(right > m_sectorsAmount.x)
		right = m_sectorsAmount.x;
	if(bottom > m_sectorsAmount.y)
		bottom = m_sectorsAmount.y;
	//draw'em
	for (int y = top; y < bottom; y++)
		{
			for (int x = left; x < right; x++)
			{
				target.draw(sectors[y*m_sectorsAmount.y+x]);
			}
		}
}
//p1,p2 pixel perfect coords
std::vector<Tile> TileMap::getCollidingWith(sf::Vector2i p1, sf::Vector2i p2) const
{
	std::vector<Tile> toreturn;
	sf::Vector2i p1tile = p1/static_cast<int>(m_tilesize);
	sf::Vector2i p2tile = p2/static_cast<int>(m_tilesize);
	sf::Vector2i start = p1tile;
	sf::Vector2i stop = p2tile;
	if(p1tile.x > p2tile.x)
	{
		stop = p1tile;//swap
		start = p2tile;
	}
	int maxy = stop.y;
	int miny = start.y;
	if(stop.y < start.y)
	{
		maxy = start.y;
		miny = stop.y;
	}
	bool foundnext = false;
	int nexty = start.y;
	//calculate special cases, when the line is straight or almost straight
	if(start.x == stop.x || start.y == stop.y)
	{
		int minx = start.x;
		int miny = std::min(p1tile.y,p2tile.y);
		int maxx = stop.x;
		int maxy = std::max(p1tile.y,p2tile.y);
		for (int y = miny; y <= maxy; y++)
		{
			for (int x = minx; x <= maxx; x++)
			{
				Tile get = getTileAt(x,y);
				if(get.isCollideable())
				{
					toreturn.push_back(get);
				}
			}
		}
		return toreturn;
	}
	for (int x = start.x; x <= stop.x;x++)
	{
		int currenty = nexty;
		int collumnstart = currenty;
		foundnext = false;
		while (currenty>=miny)
		{
			if(!foundnext && getTileAt(x+1,currenty).intersects(p1,p2))
			{
				foundnext = true;
				nexty = currenty;
			}
			Tile get = getTileAt(x,currenty);
			if(!get.intersects(p1,p2))
				break;
			if(get.isCollideable())
				toreturn.push_back(get);
			currenty--;
		}
		currenty = collumnstart+1;
		while (currenty<=maxy)
		{
			if(!foundnext && getTileAt(x+1,currenty).intersects(p1,p2))
			{
				foundnext = true;
				nexty = currenty;
			}
			Tile get = getTileAt(x,currenty);
			if(!get.intersects(p1,p2))
				break;
			if(get.isCollideable())
				toreturn.push_back(get);
			currenty++;
		}
	}
	return toreturn;
}