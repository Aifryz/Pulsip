#include"Pulsip/Rectangle.hpp"
#include"gtest/gtest.h"
#include<cmath>
class RectangleTest: public testing::Test
{
public:
	virtual void SetUp()
	{
		positive = pul::AABB(sf::Vector2f(200.f, 200.f), sf::Vector2f(80.f,80.f));
		negative = pul::AABB(sf::Vector2f(-200.f, -200.f), sf::Vector2f(80.f, 80.f));
		mid = pul::AABB(sf::Vector2f(0.f, 0.f), sf::Vector2f(20.f, 20.f));
	}
	//virtual void TearDown(){}
	pul::AABB positive;
	pul::AABB negative;
	pul::AABB mid;

	
};
TEST(RectangleConstructor, EqualityTest)
{
	pul::AABB value(-20.f, 20.f, -20.f, 20.f);
	pul::AABB vector(sf::Vector2f(), sf::Vector2f(40.f, 40.f));
	ASSERT_TRUE(value == vector);
}
TEST(RectangleConstructor, NegativeSize)
{
	pul::AABB neg(sf::Vector2f(), sf::Vector2f(-40.f, -40.f));
	pul::AABB pos(sf::Vector2f(), sf::Vector2f(40.f, 40.f));
	ASSERT_TRUE(neg == pos);
}

TEST_F(RectangleTest, Point)
{
	ASSERT_TRUE(positive.contains(170.f, 170.f));
	ASSERT_TRUE(positive.contains(sf::Vector2f(200.f, 200.f)));
	ASSERT_FALSE(positive.contains(-50.f, -50.f));
	ASSERT_FALSE(positive.contains(sf::Vector2f(-90.f, -90.f)));
	ASSERT_FALSE(positive.contains(sf::Vector2f(800.f, 800.f)));
}
TEST_F(RectangleTest, Rectangle)
{
	//positive = pul::AABB(sf::Vector2f(200.f, 200.f), sf::Vector2f(80.f, 80.f));
	//negative = pul::AABB(sf::Vector2f(-200.f, -200.f), sf::Vector2f(80.f, 80.f));
	//mid = pul::AABB(sf::Vector2f(0.f, 0.f), sf::Vector2f(20.f, 20.f));
	pul::AABB r1 = pul::AABB(sf::Vector2f(200.f, 200.f), sf::Vector2f(50.f, 50.f));
	ASSERT_TRUE(positive.contains(r1));
	ASSERT_FALSE(positive.contains(negative));
	ASSERT_FALSE(positive.contains(positive));
	ASSERT_FALSE(mid.contains(r1));
}
TEST_F(RectangleTest, RectangleIntersect)
{

	ASSERT_TRUE(positive.intersects(pul::AABB(sf::Vector2f(180.f, 180.f), sf::Vector2f(50.f, 50.f))));
	ASSERT_TRUE(negative.intersects(pul::AABB(sf::Vector2f(-180.f, -180.f), sf::Vector2f(50.f, 50.f))));
	ASSERT_FALSE(mid.intersects(positive));
}