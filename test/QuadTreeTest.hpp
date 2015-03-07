#include"Pulsip\QuadTree.hpp"
#include"Pulsip\Moveable.hpp"
#include"gtest\gtest.h"
#include"QuadTreeShallowTest.hpp"
class QuadTreeTest : public testing::Test
{
public:
	QuadTreeTest() :quadtree(pul::AABB(0.f,500.f,0.f,500.f)){}
	virtual void SetUp()
	{}
	pul::QuadTree quadtree;
};
TEST(QuadTreeShortTest, InsertionCheck)
{
	pul::QuadTree qt(pul::AABB(0.f, 500.f, 0.f, 500.f));
	std::vector<pul::QuadTreeOccupant::Ptr> objects;
	for (size_t i = 0; i < 50; i++)
	{
		objects.push_back(std::make_shared<QTO>(pul::AABB(sf::Vector2f(i, 20.f), sf::Vector2f(10.f, 10.f))));
		qt.addObject(objects[i]);
	}
	ASSERT_EQ(objects.size(), qt.size());
}
TEST(QuadTreeShortTest, RemovalCheck)
{
	pul::QuadTree qt(pul::AABB(0.f, 500.f, 0.f, 500.f));
	std::vector<pul::QuadTreeOccupant::Ptr> objects;
	for (size_t i = 0; i < 50; i++)
	{
		objects.push_back(std::make_shared<QTO>(pul::AABB(sf::Vector2f(i, 20.f), sf::Vector2f(10.f, 10.f))));
		qt.addObject(objects[i]);
	}
	ASSERT_EQ(objects.size(), qt.size());
	for (size_t i = 0; i < 50; i++)
	{
		qt.removeObject(objects[i]);
	}
	ASSERT_EQ(qt.size(), 0);
}

TEST_F(QuadTreeTest, SizeCheck)
{

}
//TODO add quad tree tests
///Adding test
///moving test(and update)
///removal test
///
///but first structures

///Mockup quadtree ocupant