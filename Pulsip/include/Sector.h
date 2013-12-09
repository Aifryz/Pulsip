#ifndef SECTOR_H
#define SECTOR_H

#include "Tile.h"
class Sector: public sf::Drawable
{
public:
	void tick(sf::Time time);

	Tile getTileAt(int x, int y) const;
	void setTile(Tile tile);

	
	/*void setTexture(sf::Texture* texture);*/
	Sector(sf::Image tiles,int x,int y,unsigned int tilesize,sf::Texture* texture);
	Sector(){};
	

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
		states.texture = m_texture;
		target.draw(m_vertices,states);
    }
	sf::VertexArray m_vertices;
	std::vector<Tile> m_tiles;
	sf::Texture* m_texture; 
	sf::Vector2i m_pos;
	unsigned int m_tilesize;
};

#endif //SECTOR_H
