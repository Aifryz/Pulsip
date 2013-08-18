#include"../include/Sector.h"

Sector::Sector(sf::Image tiles_,int x_,int y_,sf::Texture* texture)
{
	this->texture = texture;
	pos = sf::Vector2i(x_,y_);
	vertices.resize(1024);
	vertices.setPrimitiveType(sf::Quads);
	for(unsigned int y = 0;y<16;y++)
	{
		for(unsigned int x = 0;x<16;x++)
		{
			int type = tiles_.getPixel(x,y).r;
			tiles.push_back(Tile(type,x_ +x*32,y_+ y*32));

			int tilex = type%16;
			int	tiley = type/16;
			vertices[4*(y*16+x)].position = sf::Vector2f(x_ + 32*x    ,y_ + 32*y);
			vertices[4*(y*16+x)+1].position = sf::Vector2f(x_ +32*x+32,y_ + 32*y);
			vertices[4*(y*16+x)+2].position = sf::Vector2f(x_ +32*x+32,y_ + 32*y+32);
			vertices[4*(y*16+x)+3].position = sf::Vector2f(x_ +32*x   ,y_ + 32*y+32);

			vertices[4*(y*16+x)].texCoords = sf::Vector2f(tilex*32,tiley*32);
			vertices[4*(y*16+x)+1].texCoords = sf::Vector2f(tilex*32+32,tiley*32);
			vertices[4*(y*16+x)+2].texCoords = sf::Vector2f(tilex*32+32,tiley*32+32);
			vertices[4*(y*16+x)+3].texCoords = sf::Vector2f(tilex*32,tiley*32+32);
		}
	}

}
Tile Sector::getTileAt(int x, int y) const
{
	int mx = x%16;
	int my = y%16;
	return tiles[my*16+mx];
}
void Sector::setTile(Tile tile)//dodaj vertices
{
	int x = tile.getPosition().x/32;
	int y = tile.getPosition().y/32;
	tiles[y*16+x] = tile;

	int type = tile.getType();
	int tilex = type%16;
	int	tiley = type/16;

	vertices[4*(y*16+x)].texCoords = sf::Vector2f(tilex*32,tiley*32);
	vertices[4*(y*16+x)+1].texCoords = sf::Vector2f(tilex*32+32,tiley*32);
	vertices[4*(y*16+x)+2].texCoords = sf::Vector2f(tilex*32+32,tiley*32+32);
	vertices[4*(y*16+x)+3].texCoords = sf::Vector2f(tilex*32,tiley*32+32);

}
	