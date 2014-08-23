#include"Pulsip/TileMapFace.hpp"

namespace pul
{
	TileMapFace::TileMapFace(std::vector<sf::Vertex*> vertices)
	{
		m_vertices = vertices;
	}
	void TileMapFace::setTextureRectangle(sf::FloatRect rect)
	{
		m_vertices[0]->texCoords = sf::Vector2f(rect.left, rect.top);
		m_vertices[1]->texCoords = sf::Vector2f(rect.left, rect.top + rect.height);
		m_vertices[2]->texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
		m_vertices[3]->texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
		
	}
	void TileMapFace::setColor(sf::Color c)
	{
		m_vertices[0]->color = c;
		m_vertices[1]->color = c;
		m_vertices[2]->color = c;
		m_vertices[3]->color = c;
	}

	sf::FloatRect TileMapFace::getTextureRect()
	{
		sf::Vector2f position = m_vertices[0]->texCoords;
		sf::Vector2f size = position - m_vertices[3]->texCoords;
		return sf::FloatRect(position, size);
	}
	sf::Color TileMapFace::getColor()
	{
		return m_vertices[0]->color;
	}
}