#ifndef PULSIP_SEGMENT_HPP
#define PULSIP_SEGMENT_HPP
#include<SFML/Graphics.hpp>
#include<Pulsip/Util.hpp>
namespace pul
{
    ///Struct used to initialise tilemap
    struct TileMapConfig
    {
        sf::Vector2u tile_amount = { 0, 0 };
        sf::Vector2u segment_amount = { 0, 0 };
        sf::Vector2f tile_size = { 32.f, 32.f };
        sf::Vector2u segment_size = { 16U, 16U };
        size_t num_layers = 1U;
    };
    //Tilemap stores only one tile per position, so one tile can have multiple types/texture rectangles
    //Segment does not know where in the world it is
    template<class TileType>
    class Segment: public sf::Drawable
    {
    public:
        ///Default constructor
        Segment();
        ///Creates or recreates segment with given config and position(in segments)
        void create(TileMapConfig config, sf::Vector2u position);
        ///Sets the texture rectangle for tile at given position in segment [and layer]
        void setTextureRectangle(sf::FloatRect rect, sf::Vector2u position, size_t layer = 0);
        ///Returns reference to tile at given position, "position" is local to the segment(call with{0,0} will get topleft tile in seg.)
        TileType& getTileAt(sf::Vector2u position);
        ///Returns reference to tile at given position, "position" is local to the segment(call with{0,0} will get topleft tile in seg.)(const version)
        const TileType& getTileAt(sf::Vector2u position) const;
    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        sf::VertexArray m_vertices;
        std::vector<TileType> m_tiles;
        TileMapConfig m_config;
        sf::Vector2u m_position;
    };
    #include<Pulsip/Segment.inl>
}
#endif // !PULSIP_SEGMENT_HPP
