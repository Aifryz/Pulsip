#ifndef PULSIP_TILE_MAP_INL
#define PULSIP_TILE_MAP_INL
namespace
{
    template<class T>
    sf::Vector2<T> cwiseProduct(sf::Vector2<T> a, sf::Vector2<T> b)
    {
        return sf::Vector2<T>(a.x * b.x, a.y * b.y);
    }
    template<class T>
    sf::Vector2<T> cwiseQuotient(sf::Vector2<T> a, sf::Vector2<T> b)
    {
        return sf::Vector2<T>(a.x/b.x,a.y/b.y);
    }
    template<class T>
    sf::Vector2<T> cwiseModulo(sf::Vector2<T> a, sf::Vector2<T> b)
    {
        return sf::Vector2<T>(a.x % b.x, a.y % b.y);
    }
}
template<class TileType, class SegmentType>
TileMap<TileType, SegmentType>::TileMap():
    m_texture(nullptr)
{
    //Empty constructor, all data members initialised properly
}

template<class TileType, class SegmentType>
void TileMap<TileType,SegmentType>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{//TODO cleanup
    //Get world coordinates of View corners
    sf::Vector2f vtopleft = target.getView().getCenter() - (target.getView().getSize() / 2.f);
    sf::Vector2f vdownright = target.getView().getCenter() + (target.getView().getSize() / 2.f);
    //Convert global coords to chunk indices
    sf::Vector2f segmentsize = cwiseProduct(static_cast<sf::Vector2f>(m_config.segment_size), m_config.tile_size);
    
    sf::Vector2i topleft = static_cast<sf::Vector2i>(cwiseQuotient(vtopleft, segmentsize));
    sf::Vector2i downright = static_cast<sf::Vector2i>(cwiseQuotient(vdownright, segmentsize));

    //Clip indices to bounds
    topleft = clip(topleft, sf::Vector2i(0,0), static_cast<sf::Vector2i>(m_config.segment_amount) - sf::Vector2i(1, 1));
    downright = clip(downright, sf::Vector2i(0, 0), static_cast<sf::Vector2i>(m_config.segment_amount) - sf::Vector2i(1, 1));

    sf::Vector2u utopleft = static_cast<sf::Vector2u>(topleft);
    sf::Vector2u udownright = static_cast<sf::Vector2u>(downright);
    //Draw segments from topleft to downright
    states.texture = m_texture;
    for (size_t x = utopleft.x; x < udownright.x; x++)
    {
        for (size_t y = utopleft.y; y < udownright.y; y++)
        {
            target.draw(m_segments[indexify(sf::Vector2u(x,y), m_config.segment_amount)], states);
        }
    }
    return;
}

template<class TileType, class SegmentType>
void TileMap<TileType, SegmentType>::create(TileMapConfig config)
{
    m_config = config;
    size_t segx = config.tile_amount.x / config.segment_size.x;
    size_t segy = config.tile_amount.y / config.segment_size.y;
    if (config.tile_amount.x % config.segment_size.x != 0)
        segx++;
    if (config.tile_amount.y % config.segment_size.y != 0)
        segy++;
    m_segments.resize(segx*segy);
    m_config.segment_amount = sf::Vector2u(segx, segy);
    for (size_t x = 0; x < segx; x++)
    {
        for (size_t y = 0; y < segy; y++)
        {
            m_segments[indexify(sf::Vector2u(x, y), sf::Vector2u(segx, segy))].create(m_config, sf::Vector2u(x, y));
        }
    }
}

template<class TileType, class SegmentType>
TileType& TileMap<TileType, SegmentType>::getTileAt(sf::Vector2u position)
{
    return getSegmentAtTilePos(position).getTileAt(cwiseModulo(position,m_config.segment_size));
}
template<class TileType, class SegmentType>
const TileType& TileMap<TileType, SegmentType>::getTileAt(sf::Vector2u position) const
{
    return getSegmentAtTilePos(position).getTileAt(cwiseModulo(position, m_config.segment_size));
}
template<class TileType, class SegmentType>
void TileMap<TileType, SegmentType>::setTexture(const sf::Texture& texture)
{
    m_texture = texture;
}
template<class TileType, class SegmentType>
SegmentType& TileMap<TileType, SegmentType>::getSegment(sf::Vector2u position)
{
    return m_segments[indexify(position, m_config.segment_amount)];
}
template<class TileType, class SegmentType>

const SegmentType& TileMap<TileType, SegmentType>::getSegment(sf::Vector2u position) const
{
    return m_segments[indexify(position, m_config.segment_amount)];
}

template<class TileType, class SegmentType>
SegmentType& TileMap<TileType, SegmentType>::getSegmentAtTilePos(sf::Vector2u position)
{
    sf::Vector2u seg = cwiseQuotient(position, m_config.segment_size);
    return getSegment(seg);
}

template<class TileType, class SegmentType>
const SegmentType& TileMap<TileType, SegmentType>::getSegmentAtTilePos(sf::Vector2u position) const
{
    sf::Vector2u seg = cwiseQuotient(position, m_config.segment_size);
    return getSegment(seg);
}

template<class TileType, class SegmentType>
void TileMap<TileType, SegmentType>::setTextureRectangle(sf::FloatRect rect, sf::Vector2u position, size_t layer)
{
    getSegmentAtTilePos(position).setTextureRectangle(rect, cwiseModulo(position, m_config.segment_size), layer);
}

#endif // !PULSIP_TILE_MAP_INL
