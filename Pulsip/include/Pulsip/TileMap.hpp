#ifndef PULSIP_TILE_MAP_HPP
#define PULSIP_TILE_MAP_HPP
#include<memory>
#include<Pulsip/Segment.hpp>
#include<Pulsip/Util.hpp>
namespace pul
{
	
    //TileType requires[TODO Add documentation]
	template<class TileType, class SegmentType=Segment<TileType>>
    class TileMap: sf::Drawable
    {
    public:
        ///Default constructor
        TileMap();

        ///Creates tilemap with given config
        void create(TileMapConfig config);

        ///Returns reference to tile at given position
        TileType& getTileAt(sf::Vector2u position);

        ///Returns reference to tile at given position(const version)
        const TileType& getTileAt(sf::Vector2u position) const;

        ///Sets the texture for the TileMap
        void setTexture(const sf::Texture& texture);

        ///Returns reference to segment at given index
        SegmentType& getSegment(sf::Vector2u position);

        ///Returns reference to segment at given index
        const SegmentType& getSegment(sf::Vector2u position) const;

        ///Returns reference to segment which contains tile at given position
        SegmentType& getSegmentAtTilePos(sf::Vector2u position);

        ///Returns reference to segment which contains tile at given position
        const SegmentType& getSegmentAtTilePos(sf::Vector2u position) const;

        ///Sets the texture rectangle for tile at given position in segment [and layer]
        void setTextureRectangle(sf::FloatRect rect, sf::Vector2u position, size_t layer = 0);
    protected:
        const sf::Texture* m_texture;
        std::vector<SegmentType> m_segments;
        TileMapConfig m_config;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
    #include<Pulsip\TileMap.inl>
}
#endif // !PULSIP_TILE_MAP_HPP
