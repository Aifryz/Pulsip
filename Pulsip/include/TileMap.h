#ifndef TILEMAP_H
#define TILEMAP_H

#include"Sector.h"
#include"GameObject.h"
class TileMap: public sf::Drawable
{
public:
	TileMap(sf::Texture* texture);
	TileMap(){};
	void tick(sf::Time time);
	void load();
	sf::Vector2u getSectorsAmount() const;
	sf::Vector2u getSize() const;
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
};
#endif // !TILEMAP_H
