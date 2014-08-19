#ifndef PULSIP_TILE_MAP_HPP
#define PULSIP_TILE_MAP_HPP
#include<vector>
#include<memory>
#include<SFML/Graphics.hpp>
#include<Pulsip/TileMapFace.hpp>
namespace pul
{
	/** Class representing multi-layer TileMap
	*	This class can be used as a standalone tilemap or can be element in more complex system
	*
	*/
	class PULSIP_API TileMap : public sf::Drawable, public sf::Transformable, sf::NonCopyable
	{
	public:
		///Creates empty tilemap
		TileMap(sf::Vector2f tilesize = sf::Vector2f(32.f, 32.f), size_t layers = 1);
		///Creates tilemap with given texture, amount of tiles, tilesize and amount of layers
		TileMap(const sf::Texture& texture, sf::Vector2u tileamount, sf::Vector2f tilesize = sf::Vector2f(32.f, 32.f), size_t layers = 1);

		///Returns face at given index
		///This method ignores transform and tile size
		TileMapFace::Ptr getFaceAtIndex(unsigned int x, unsigned int y, unsigned int layer = 0) const;

		///Returns face at given coordinates
		///This method takes in account transform and tilesize
		TileMapFace::Ptr getFace(float x, float y, unsigned int layer = 0) const;

		///Returns face at given index
		///This method ignores transform and tile size
		TileMapFace::Ptr getFaceAtIndex(sf::Vector2u position, unsigned int layer = 0) const;

		///Returns face at given coordinates
		///This method takes in account transform and tilesize
		TileMapFace::Ptr getFace(sf::Vector2f position, unsigned int layer = 0) const;

		const sf::Vector2f& getTileSize() const;

		///Returns the size(in amount of tiles) of the TileMap
		const sf::Vector2u& getTileAmount() const;
		///Returns the amount of layers
		size_t getLayerAmount() const;

		void setTexture(const sf::Texture& texture);
		const sf::Texture* getTexture() const;

		///Resizes the tilemap.
		///This method won't invalidate TileMapFace pointers, so it's safe to store them outside of TileMap
		void resize(sf::Vector2u tileamount);

	private:
		std::vector<std::vector<TileMapFace::Ptr>> m_layers;
		sf::Vector2f m_position;
		sf::Vector2f m_tilesize;
		sf::Vector2u m_tileamount;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		std::vector<sf::Vertex> m_vertices;
		const sf::Texture* m_texture;
	};
}
#endif // !PULSIP_TILE_MAP_HPP
