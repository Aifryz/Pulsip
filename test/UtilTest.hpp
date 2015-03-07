#include"gtest/gtest.h"
#include"Pulsip/Util.hpp"
#include<random>
#include<functional>
TEST(Util_fastRemove, ZeroSizeCheck)
{
	
	std::vector<int> data1{ 1, 2, 3, 4 };
	std::vector<int>data2{ 1 };
	pul::fastErase(data2, 0);
	pul::fastErase(data1, 1);
	ASSERT_EQ(data1[1], 4);
	ASSERT_EQ(data2.size(),0);
}
TEST(Util_indexify,ResultCheck)
{
    sf::Vector2i size(2, 2);
    sf::Vector2i pos1(1, 1);
    sf::Vector2i pos2(0, 1);

    ASSERT_EQ(pul::indexify(pos1, size), 3);
    ASSERT_EQ(pul::indexify(pos2, size), 2);
}
TEST(Util_indexify, Reversibility)
{
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distr(0,49);
    auto random = std::bind(distr, engine);

    sf::Vector2i size(50, 50);
    for (size_t i = 0; i < 10; i++)
    {
        int test = random();
        ASSERT_EQ(test, pul::indexify(pul::deindexify(test, size), size));
        ASSERT_NE(test + 1, pul::indexify(pul::deindexify(test, size), size));
    }
}
TEST(Util_clip, Vector)
{
    sf::Vector2f min = { 0.f, 0.f };
    sf::Vector2f max = {100.f, 100.f};
    ASSERT_EQ(pul::clip(sf::Vector2f(5000.f, 5000.f), min, max), max);
    ASSERT_EQ(pul::clip(sf::Vector2f(-1.f, -1.f), min, max), min);
    ASSERT_EQ(pul::clip(sf::Vector2f(10.f, 10.f), min, max), sf::Vector2f(10.f,10.f));
}