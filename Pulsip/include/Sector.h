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
	Sector(sf::Image tiles,int x,int y,sf::Texture* texture);
	Sector(){};
	

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
		states.texture = texture;
		target.draw(vertices,states);
    }
	sf::VertexArray vertices;
	std::vector<Tile> tiles;
	sf::Texture* texture; 
	sf::Vector2i pos;
};

#endif //SECTOR_H
