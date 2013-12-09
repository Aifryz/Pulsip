#include"../include/Sector.h"

Sector::Sector(sf::Image tiles,int x,int y,unsigned int tilesize,sf::Texture* texture):
	m_tilesize(tilesize),
	m_texture(texture),
	m_pos(x,y)
{
	m_vertices.resize(16*16*4);
	m_vertices.setPrimitiveType(sf::Quads);
	for(unsigned int yi = 0;yi<16;yi++)
	{
		for(unsigned int xi = 0;xi<16;xi++)
		{
			int type = tiles.getPixel(xi,yi).r;
			m_tiles.push_back(Tile(type,x +xi*m_tilesize,y+ yi*m_tilesize));

			int tilex = type%16;
			int	tiley = type/16;
			m_vertices[4*(yi*16+xi)  ].position = sf::Vector2f(x + m_tilesize*xi  , y + m_tilesize*yi);
			m_vertices[4*(yi*16+xi)+1].position = sf::Vector2f(x + m_tilesize*xi+m_tilesize,y + m_tilesize*yi);
			m_vertices[4*(yi*16+xi)+2].position = sf::Vector2f(x + m_tilesize*xi+m_tilesize,y + m_tilesize*yi+m_tilesize);
			m_vertices[4*(yi*16+xi)+3].position = sf::Vector2f(x + m_tilesize*xi  , y + m_tilesize*yi+m_tilesize);

			m_vertices[4*(yi*16+xi)  ].texCoords = sf::Vector2f(tilex*m_tilesize , tiley*m_tilesize);
			m_vertices[4*(yi*16+xi)+1].texCoords = sf::Vector2f(tilex*m_tilesize+m_tilesize , tiley*m_tilesize);
			m_vertices[4*(yi*16+xi)+2].texCoords = sf::Vector2f(tilex*m_tilesize+m_tilesize , tiley*m_tilesize+m_tilesize);
			m_vertices[4*(yi*16+xi)+3].texCoords = sf::Vector2f(tilex*m_tilesize , tiley*m_tilesize+m_tilesize);
		}
	}

}
Tile Sector::getTileAt(int x, int y) const
{
	int mx = x%16;
	int my = y%16;
	return m_tiles[my*16+mx];
}
void Sector::setTile(Tile tile)//dodaj vertices
{
	int x = tile.getPosition().x/m_tilesize;
	int y = tile.getPosition().y/m_tilesize;
	m_tiles[y*16+x] = tile;

	int type = tile.getType();
	int tilex = type%16;
	int	tiley = type/16;

	m_vertices[4*(y*16+x)  ].texCoords = sf::Vector2f(tilex*m_tilesize , tiley*m_tilesize);
	m_vertices[4*(y*16+x)+1].texCoords = sf::Vector2f(tilex*m_tilesize+m_tilesize , tiley*m_tilesize);
	m_vertices[4*(y*16+x)+2].texCoords = sf::Vector2f(tilex*m_tilesize+m_tilesize , tiley*m_tilesize+m_tilesize);
	m_vertices[4*(y*16+x)+3].texCoords = sf::Vector2f(tilex*m_tilesize , tiley*m_tilesize+m_tilesize);

}
	