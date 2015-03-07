#include<Pulsip/TileMap.hpp>
#include"gtest/gtest.h"
namespace
{
    struct Tile
    {
    public:
        Tile(int type) :m_type(type){}
        int getType(){ return m_type; }
    private:
        int m_type;
    };
    class TileMapImpl : public pul::TileMap<Tile>
    {
    public:
        void create(pul::TileMapConfig cfg)
        {
            pul::TileMap<Tile>::create(cfg);
            for (size_t i = 0; i < cfg.tile_amount.x*cfg.tile_amount.y; i++)
            {
                getTileAt(pul::deindexify(i, cfg.tile_amount)) = Tile(1);
            }
        }
    private:
    };
}
TEST(TileMapImplementationTest, Construction)
{
    TileMapImpl map;
    pul::TileMapConfig cfg;
    cfg.num_layers = 3;
    cfg.tile_amount = { 50U, 50U };
    map.create(cfg);
    ASSERT_EQ(map.getTileAt({ 49U, 49U }), 1);
}
TEST(TileMapImplementationTest, Acces)
{
    TileMapImpl map;
    pul::TileMapConfig cfg;
    cfg.num_layers = 3;
    cfg.tile_amount = { 50U, 50U };
    map.create(cfg);
    map.getTileAt({ 10U, 10U }) = Tile(5);
    ASSERT_EQ(map.getTileAt({ 10U, 10U }).getType(), 5);
}
