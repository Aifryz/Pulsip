#ifndef PULSIP_SEGMENT_INL
#define PULSIP_SEGMENT_INL
template<class TileType>
Segment<TileType>::Segment()
{
    //Empty constructor, all data members properly initialised
}
template<class TileType>
void Segment<TileType>::create(TileMapConfig config, sf::Vector2u position)
{
    m_config = config;
	m_vertices.resize(config.segment_size.x*config.segment_size.y*config.num_layers*4);
    m_tiles.resize(config.segment_size.x*config.segment_size.y);
    //Reposition vertices
    for (size_t i = 0; i < config.num_layers; i++)
    {
        for (size_t x = 0; x < config.segment_size.x; x++)
        {
            for (size_t y = 0; y < config.segment_size.y; y++)
            {
                size_t layer_offset = i*(m_config.segment_size.x*m_config.segment_size.y);
                size_t quad_offset = indexify(sf::Vector2u(x,y), m_config.segment_size) * 4;
                sf::Vector2f quad_pos = sf::Vector2f(x*m_config.tile_size.x, y*m_config.tile_size.y);
                m_vertices[layer_offset + quad_offset + 0].texCoords = quad_pos + sf::Vector2f(0.f, 0.f);
                m_vertices[layer_offset + quad_offset + 1].texCoords = quad_pos + sf::Vector2f(0.f, m_config.tile_size.y);
                m_vertices[layer_offset + quad_offset + 2].texCoords = quad_pos + sf::Vector2f(m_config.tile_size.x, m_config.tile_size.y);
                m_vertices[layer_offset + quad_offset + 3].texCoords = quad_pos + sf::Vector2f(m_config.tile_size.x, 0.f);
            }
        }
       
    }
}
template<class TileType>
void Segment<TileType>::setTextureRectangle(sf::FloatRect rect, sf::Vector2u position, size_t layer)
{
    size_t layer_offset = layer*(m_config.segment_size.x*m_config.segment_size.y);
    size_t quad_offset = indexify(position, m_config.segment_size)*4;
    m_vertices[layer_offset + quad_offset + 0].texCoords = sf::Vector2f(rect.left,rect.top);
    m_vertices[layer_offset + quad_offset + 1].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);
    m_vertices[layer_offset + quad_offset + 2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    m_vertices[layer_offset + quad_offset + 3].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
}

template<class TileType>
TileType& Segment<TileType>::getTileAt(sf::Vector2u position)
{
    return m_tiles[indexify(position, m_config.segment_size)];
}
template<class TileType>
const TileType& Segment<TileType>::getTileAt(sf::Vector2u position) const
{
    return m_tiles[indexify(position, m_config.segment_size)];
}
template<class TileType>
void Segment<TileType>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Set translation to current position
    sf::Vector2f offset = sf::Vector2f(m_position.x*m_config.segment_size.x*m_config.tile_size.x, m_position.y*m_config.segment_size.y*m_config.tile_size.y);
    states.transform.translate(offset);
    target.draw(m_vertices, states);
}
#endif // !PULSIP_SEGMENT_INL
