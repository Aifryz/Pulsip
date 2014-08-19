#ifndef PULSIP_TILE_MAP_FACE_HPP
#define PULSIP_TILE_MAP_FACE_HPP
#include <SFML/Graphics.hpp>
#include <Pulsip/Config.hpp>
#include <memory>
namespace pul
{
	class PULSIP_API TileMapFace : sf::NonCopyable
	{
	public:
		void setTextureRectangle(sf::FloatRect rect);
		void setColor(sf::Color);
		
		sf::FloatRect getTextureRect();
		sf::Color getColor();

		typedef std::shared_ptr<TileMapFace> Ptr;
	private:
		friend class TileMap;
		TileMapFace(std::vector<sf::Vertex*> vertices);
		std::vector<sf::Vertex*> m_vertices;
	};
}
#endif // !PULSIP_TILE_MAP_FACE_HPP
