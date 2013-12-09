#ifndef TILEMAP_H
#define TILEMAP_H

#include"Sector.h"
#include"GameObject.h"
class TileMap: public sf::Drawable
{
public:
	TileMap(sf::Texture* texture, unsigned int tilesize, sf::Vector2i starting_pos = sf::Vector2i(0,0));
	void tick(sf::Time time);
	//loads tilemap from image
	void load(std::string name);
	sf::Vector2u getSectorsAmount() const;
	sf::Vector2u getSize() const;
	sf::Vector2u getTileSize() const;
	sf::Vector2i getStartingPos() const;
	Tile getTileAt(int x, int y) const;
	void setTile(Tile tile);
	

	std::vector<Tile> getCollidingWith(GameObject*object) const;
	std::vector<Tile> getCollidingWith(sf::IntRect rect) const;
	std::vector<Tile> getCollidingWith(sf::Vector2i p1, sf::Vector2i p2) const;
	std::vector<Tile> getCollidingWithDbg(sf::Vector2i p1, sf::Vector2i p2) const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<Sector> sectors;

	sf::Texture* m_texture; 
	sf::Vector2u m_sectorsAmount;
	sf::Vector2u m_size;
	unsigned int m_tilesize;
	sf::Vector2i m_starting_pos;
};
#endif // !TILEMAP_H
