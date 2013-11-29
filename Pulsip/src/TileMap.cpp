#include"../include/TileMap.h"
TileMap::TileMap(sf::Texture* texture)
{
	m_texture = texture;
	load();
}
void TileMap::load()
{
	
	sf::Image map;
	map.loadFromFile("mapa.png");
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
			sectors[y*m_sectorsAmount.y+x] = Sector(dest,x*512,y*512,m_texture);
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
	
	int x = tile.getPosition().x/32;
	int y = tile.getPosition().y/32;
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
	std::vector<Tile> returntiles;
	
	sf::IntRect rect = static_cast<sf::IntRect>( object->getColRect() );

		sf::Vector2i NW((rect.left)/32           ,(rect.top)/32);
		sf::Vector2i SE((rect.left+rect.width)/32   ,(rect.top+rect.height)/32);

		sf::Vector2i ds = SE-NW;

		if(ds.x == 0 && ds.y == 0)
		{
			Tile get = getTileAt(NW.x,NW.y);
			if(get.isCollideable())
				returntiles.push_back(get);
			return returntiles;
		}
		if(ds.x == 0)
		{
			for (int y = NW.y; y <= SE.y; y++)
			{
				Tile get = getTileAt(SE.x,y);
				if(get.isCollideable())
					returntiles.push_back(get);
			}
			return returntiles;
		}
		if(ds.y == 0)
		{
			for (int x = NW.x; x <= SE.x; x++)
			{
				Tile get = getTileAt(x,SE.y);

				if(get.isCollideable())
					returntiles.push_back(get);
			}
			return returntiles;
		}
		//else
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
	sf::Vector2u pos = static_cast<sf::Vector2u>(target.getView().getCenter() - target.getView().getSize()/2.f);
	sf::Vector2u  size = static_cast<sf::Vector2u>(target.getView().getSize());
	unsigned int left = pos.x/512;
	unsigned int top = pos.y/512;
	unsigned int right = (pos.x +size.x)/512 +1;
	unsigned int bottom = (pos.y + size.y)/512 +1;
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
	for (unsigned int y = top; y < bottom; y++)
		{
			for (unsigned int x = left; x < right; x++)
			{
				target.draw(sectors[y*m_sectorsAmount.y+x]);
			}
		}
	
	

	

}
