#include"gtest/gtest.h"
#include<Pulsip/TileMap.hpp>
namespace
{
    struct Tile
    {
        int type;
    };
}
//#include"TileMapVisualTest.hpp"
TEST(TileMapShortTest, Create)
{
    pul::TileMapConfig cfg1;
    pul::TileMapConfig cfg2;
    cfg1.num_layers = 1;
    cfg1.tile_amount = { 32, 32 };
    cfg2.num_layers = 2;
    cfg2.tile_amount = { 33, 33 };
    pul::TileMap<Tile> map;
    map.create(cfg1);
    pul::TileMap<Tile> map2;
    map2.create(cfg2);

}
TEST(TileMapShortTest, SetAndRetrieve)
{
    
    pul::TileMapConfig cfg;
    cfg.num_layers = 1;
    cfg.tile_amount = { 32U, 32U };
    pul::TileMap<Tile> map;
    map.create(cfg);
    map.getTileAt({ 1U, 1U }).type = 1;
    map.getTileAt({ 31U, 31U }).type = 2;

    ASSERT_EQ(map.getTileAt({ 1U, 1U }).type, 1);
    ASSERT_EQ(map.getTileAt({ 31U, 31U }).type, 2);
}
//TEST(TileMapShortTest,Create)
//{
//	pul::TileMap tm;
//	pul::TileMap tm2(sf::Vector2f(35.f, 35.f), 5U);
//}
//TEST(TileMapShortTest, Resize)
//{
//	pul::TileMap tm;
//	tm.resize(sf::Vector2u(10U, 10U));
//}
//TEST(TileMapShortTest, GetFaceNoDisplacement)
//{
//	sf::Texture txt;
//	pul::TileMap tm(txt,sf::Vector2u(32U,32U),sf::Vector2f(10.f,10.f),1);
//	ASSERT_EQ(tm.getFaceAtIndex(1U, 1U), tm.getFace(11.f, 11.f));
//	ASSERT_NE(tm.getFaceAtIndex(5U, 5U), tm.getFace(11.f, 11.f));
//}
//TEST(TileMapShortTest, GetFaceWithDisplacement)
//{
//	sf::Texture txt;
//	pul::TileMap tm(txt, sf::Vector2u(32U, 32U), sf::Vector2f(10.f, 10.f), 1);
//	tm.setPosition(300.f, 300.f);
//	ASSERT_EQ(tm.getFaceAtIndex(1U, 1U), tm.getFace(311.f, 311.f));
//	ASSERT_NE(tm.getFaceAtIndex(5U, 5U), tm.getFace(311.f, 311.f));
//}
//TEST(TileMapShortTest, ResizeTest)
//{
//	pul::TileMap tm;
//	tm.resize(sf::Vector2u(50U, 50U));
//	tm.resize(sf::Vector2u(10U, 10U));
//}
//TEST(TileMapShortTest, PointerValidityCheck)
//{
//	sf::Texture txt;
//	pul::TileMap tm(txt, sf::Vector2u(32U, 32U), sf::Vector2f(10.f, 10.f), 1);
//	pul::TileMapFace::Ptr ptr = tm.getFaceAtIndex(5, 5);
//
//	tm.resize(sf::Vector2u(50U, 50U));
//
//	ASSERT_EQ(ptr.use_count(), 2);
//
//	tm.resize(sf::Vector2u(2U, 2U));
//	
//	ASSERT_EQ(ptr.use_count(), 1);
//
//}
