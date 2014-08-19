#include "Pulsip/TileMap.hpp"
namespace pul
{
	TileMap::TileMap(sf::Vector2f tilesize, size_t num_of_layers):
		m_tilesize(tilesize),
		m_texture(nullptr)
	{
		m_layers.resize(num_of_layers);
	}
	TileMap::TileMap(const sf::Texture& texture, sf::Vector2u tileamount, sf::Vector2f tilesize, size_t num_of_layers):
		m_tilesize(tilesize),
		m_texture(&texture),
		m_tileamount(tileamount)
	{
		m_layers.resize(num_of_layers);
		for (int i = 0; i < num_of_layers; i++)
		{
			m_layers[i].resize(tileamount.x*tileamount.y);
		}
		m_vertices.resize(num_of_layers *(tileamount.x*tileamount.y * 4));

		for (int i = 0; i < num_of_layers; i++)
		{
			for (size_t x = 0; x < tileamount.x; x++)
			{
				for (size_t y = 0; y < tileamount.y; y++)
				{
					sf::Vertex* layerstart = &m_vertices[i*(tileamount.x*tileamount.y * 4)];
					sf::Vertex* facestart = &layerstart[(x*tileamount.y + y)*4];
					sf::Vector2f NE(x*m_tilesize.x, y*m_tilesize.y);
					
					facestart[0].position = NE;
					facestart[1].position = NE + sf::Vector2f(0.f, tilesize.y);
					facestart[2].position = NE + sf::Vector2f(tilesize.x,tilesize.y);
					facestart[3].position = NE + sf::Vector2f(tilesize.x, 0.f);
					
					std::vector<sf::Vertex*> faceverts{ facestart, facestart + 1, facestart + 2, facestart + 3 };
					
					m_layers[i][x*tileamount.y + y] = TileMapFace::Ptr(new TileMapFace(faceverts));
				}
			}
		}
	}

	void TileMap::resize(sf::Vector2u tileamount)
	{
		m_vertices.resize(m_layers.size() *(tileamount.x*tileamount.y * 4));

		for (size_t i = 0; i < m_layers.size(); i++)
		{
			std::vector<TileMapFace::Ptr> old;
			old.swap(m_layers[i]);
			m_layers[i].resize(tileamount.x*tileamount.y * 4);

			for (size_t x = 0; x < m_tileamount.x; x++)
			{
				for (size_t y = 0; y < m_tileamount.y; y++)
				{
					if (x<tileamount.x && y<tileamount.y)
						m_layers[i][x*tileamount.y + y] = old[x*m_tileamount.y + y];
				}
			}
			//if face == null create new face
			for (size_t x = 0; x < tileamount.x; x++)
			{
				for (size_t y = 0; y < tileamount.y; y++)
				{
					sf::Vertex* layerstart = &m_vertices[i*(tileamount.x*tileamount.y * 4)];
					sf::Vertex* facestart = &layerstart[(x*tileamount.y + y) * 4];
					
					std::vector<sf::Vertex*> faceverts{ facestart, facestart + 1, facestart + 2, facestart + 3 };
					if (!m_layers[i][x*tileamount.y + y])//if nullptr create new face
					{
						m_layers[i][x*tileamount.y + y] = TileMapFace::Ptr(new TileMapFace(faceverts));
					}
					else
					{//update vertices
						m_layers[i][x*tileamount.y + y]->m_vertices = faceverts;
						
					}
				}
			}
		}
		m_tileamount = tileamount;
	}
	const sf::Vector2f& TileMap::getTileSize() const
	{
		return m_tilesize;
	}
	const sf::Vector2u& TileMap::getTileAmount() const
	{
		return m_tileamount;
	}

	void TileMap::setTexture(const sf::Texture& texture)
	{
		m_texture = &texture;
	}
	const sf::Texture* TileMap::getTexture() const
	{
		return m_texture;
	}

	TileMapFace::Ptr TileMap::getFaceAtIndex(unsigned int x, unsigned int y, unsigned int layer) const
	{
		return getFaceAtIndex(sf::Vector2u(x, y), layer);
	}
	TileMapFace::Ptr TileMap::getFace(float x, float y, unsigned int layer) const
	{
		return getFace(sf::Vector2f(x, y), layer);
	}
	TileMapFace::Ptr TileMap::getFace(sf::Vector2f position, unsigned int layer) const
	{
		sf::Vector2f localposition = getInverseTransform().transformPoint(position);
		unsigned int x = static_cast<int>(localposition.x / m_tilesize.x);
		unsigned int y = static_cast<int>(localposition.y / m_tilesize.y);
		if (x < m_tileamount.x &&  y < m_tileamount.y)
			return getFaceAtIndex(sf::Vector2u(x, y), layer);
		else
			return nullptr;
	}
	TileMapFace::Ptr TileMap::getFaceAtIndex(sf::Vector2u position, unsigned int layer) const
	{
		return m_layers[layer][position.x*m_tileamount.y + position.y];
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = m_texture;
		target.draw(&m_vertices[0], m_vertices.size(), sf::PrimitiveType::Quads, states);
	}
}