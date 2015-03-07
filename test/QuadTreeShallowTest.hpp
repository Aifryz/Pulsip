#include"gtest\gtest.h"
#include"Pulsip\QuadTree.hpp"
#include"Pulsip\Moveable.hpp"
#include"gtest\gtest.h"
class QTO :public pul::QuadTreeOccupant, public pul::Moveable
{
public:
	QTO()
	{
		m_aabb = pul::AABB();
	}
	QTO(pul::AABB aabb)
	{
		m_aabb = aabb;
	}
	~QTO()
	{

	}
	virtual const pul::AABB& getAABB()
	{
		return m_aabb;
	}
	virtual sf::Vector2f getPosition() const
	{
		return m_aabb.getPosition();
	}
	virtual void tick(sf::Time dt){}
	virtual void move(sf::Vector2f offset)
	{
		setPosition(getPosition() + offset);
	}
	virtual void setPosition(sf::Vector2f pos)
	{
		m_aabb.setPosition(pos);
		updatePositionInQuadTree();
	}
private:
	pul::AABB m_aabb;
};
class QuadTreeShallowTest : public testing::Test
{
public:
	QuadTreeShallowTest():
		m_qt(pul::AABB(0.f, 500.f, 0.f, 500.f))
	{}
	virtual void SetUp()
	{
		m_objects.push_back(std::make_shared<QTO>(pul::AABB(sf::Vector2f(30.f, 30.f), sf::Vector2f(50.f, 50.f))));
		m_objects.push_back(std::make_shared<QTO>(pul::AABB(sf::Vector2f(280.f, 280.f), sf::Vector2f(50.f, 50.f))));
		m_objects.push_back(std::make_shared<QTO>(pul::AABB(sf::Vector2f(30.f, 280.f), sf::Vector2f(50.f, 50.f))));
		m_objects.push_back(std::make_shared<QTO>(pul::AABB(sf::Vector2f(280.f, 30.f), sf::Vector2f(50.f, 50.f))));
	}
	pul::QuadTree m_qt;
	std::vector<pul::QuadTreeOccupant::Ptr> m_objects;
};
TEST_F(QuadTreeShallowTest, SplitTest)
{
	m_qt.addObject(m_objects[0]);
	pul::QuadTreeNode* node1 = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NE);
	ASSERT_FALSE(node1);
	ASSERT_EQ(m_qt.getRoot()->size(), 1);

	m_qt.addObject(m_objects[1]);
	pul::QuadTreeNode* node2 = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NE);
	ASSERT_FALSE(node2);
	ASSERT_EQ(m_qt.getRoot()->size(), 2);

	m_qt.addObject(m_objects[2]);
	pul::QuadTreeNode* node3 = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NE);
	ASSERT_TRUE(node3);

	pul::QuadTreeNode* NW = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NW);
	pul::QuadTreeNode* NE = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NE);
	pul::QuadTreeNode* SW = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::SW);
	pul::QuadTreeNode* SE = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::SE);
	ASSERT_EQ(NW->size(), 1);
	ASSERT_EQ(SE->size(), 1);
	ASSERT_EQ(SW->size(), 1);
	ASSERT_EQ(NE->size(), 0);
	ASSERT_EQ(m_qt.size(), 3);
}
TEST_F(QuadTreeShallowTest, RetrievalTest)
{
	for (size_t i = 0; i < 4; i++)
	{
		m_qt.addObject(m_objects[i]);
	}
	std::vector<pul::QuadTreeOccupant::Ptr> returned;
	m_qt.pollObjects(pul::AABB(sf::Vector2f(50.f,50.f),sf::Vector2f(10.f,10.f)), returned);
	ASSERT_EQ(returned.size(), 1);
	returned.clear();

	m_qt.pollObjects(pul::AABB(sf::Vector2f(250.f, 50.f), sf::Vector2f(10.f, 10.f)), returned);
	ASSERT_EQ(returned.size(), 2);
	returned.clear();

	m_qt.pollObjects(pul::AABB(sf::Vector2f(250.f, 250.f), sf::Vector2f(10.f, 10.f)), returned);
	ASSERT_EQ(returned.size(), 4);
	returned.clear();

	m_qt.addObject(std::make_shared<QTO>(pul::AABB(sf::Vector2f(280.f, 280.f), sf::Vector2f(70.f, 70.f))));

	m_qt.pollObjects(pul::AABB(sf::Vector2f(50.f, 50.f), sf::Vector2f(10.f, 10.f)), returned);
	ASSERT_EQ(returned.size(), 2);
	returned.clear();

	m_qt.pollObjects(pul::AABB(sf::Vector2f(250.f, 50.f), sf::Vector2f(10.f, 10.f)), returned);
	ASSERT_EQ(returned.size(), 3);
	returned.clear();

	m_qt.pollObjects(pul::AABB(sf::Vector2f(250.f, 250.f), sf::Vector2f(10.f, 10.f)), returned);
	ASSERT_EQ(returned.size(), 5);
	returned.clear();
}
TEST_F(QuadTreeShallowTest, RemovalTest)
{
	for (size_t i = 0; i < 4; i++)
	{
		m_qt.addObject(m_objects[i]);
	}
	pul::QuadTreeOccupant::Ptr o1 = std::make_shared<QTO>(pul::AABB(sf::Vector2f(250.f, 250.f), sf::Vector2f(50.f, 50.f)));
	m_qt.addObject(o1);
	ASSERT_EQ(m_qt.size(), 5);
	m_qt.removeObject(o1);
	ASSERT_EQ(m_qt.size(), 4);

	m_qt.removeObject(m_objects[0]);
	ASSERT_EQ(m_qt.size(), 3);

	m_qt.removeObject(m_objects[1]);
	ASSERT_EQ(m_qt.size(), 2);

	m_qt.removeObject(m_objects[2]);
	ASSERT_EQ(m_qt.size(), 1);

	m_qt.removeObject(m_objects[3]);
	ASSERT_EQ(m_qt.size(), 0);

	pul::QuadTreeNode* NW = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NW);
	pul::QuadTreeNode* NE = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NE);
	pul::QuadTreeNode* SW = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::SW);
	pul::QuadTreeNode* SE = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::SE);
	if (NW && NE && SW && SE)
	{
		ASSERT_EQ(NW->size(), 0);
		ASSERT_EQ(NE->size(), 0);
		ASSERT_EQ(SW->size(), 0);
		ASSERT_EQ(SE->size(), 0);
	}
}
TEST_F(QuadTreeShallowTest, UpdateTest)
{
	for (size_t i = 0; i < 4; i++)
	{
		m_qt.addObject(m_objects[i]);
	}
	for (size_t i = 0; i < 4; i++)
	{
		std::static_pointer_cast<QTO>(m_objects[i])->setPosition(sf::Vector2f(30.f, 30.f));
	}
	ASSERT_EQ(m_qt.size(), 4);

	pul::QuadTreeNode* NW = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NW);
	pul::QuadTreeNode* NE = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::NE);
	pul::QuadTreeNode* SW = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::SW);
	pul::QuadTreeNode* SE = m_qt.getRoot()->getChild(pul::QuadTreeNode::Children::SE);
	ASSERT_EQ(NW->size(), 4);
	ASSERT_EQ(NE->size(), 0);
	ASSERT_EQ(SW->size(), 0);
	ASSERT_EQ(SE->size(), 0);

	pul::QuadTreeOccupant::Ptr o1 = std::make_shared<QTO>(pul::AABB(sf::Vector2f(250.f, 250.f), sf::Vector2f(50.f, 50.f)));
	m_qt.addObject(o1);
	ASSERT_EQ(m_qt.size(), 5);
	ASSERT_EQ(NW->size(), 4);
	ASSERT_EQ(NE->size(), 0);
	ASSERT_EQ(SW->size(), 0);
	ASSERT_EQ(SE->size(), 0);

	std::static_pointer_cast<QTO>(o1)->setPosition(sf::Vector2f(280.f, 280.f));

	ASSERT_EQ(m_qt.size(), 5);
	ASSERT_EQ(NW->size(), 4);
	ASSERT_EQ(NE->size(), 0);
	ASSERT_EQ(SW->size(), 0);
	ASSERT_EQ(SE->size(), 1);

	std::static_pointer_cast<QTO>(o1)->setPosition(sf::Vector2f(250.f, 250.f));

	ASSERT_EQ(m_qt.size(), 5);
	ASSERT_EQ(NW->size(), 4);
	ASSERT_EQ(NE->size(), 0);
	ASSERT_EQ(SW->size(), 0);
	ASSERT_EQ(SE->size(), 0);
	
}
TEST_F(QuadTreeShallowTest, MoveOutside)
{
	pul::QuadTreeOccupant::Ptr o1 = std::make_shared<QTO>(pul::AABB(sf::Vector2f(250.f, 250.f), sf::Vector2f(50.f, 50.f)));
	m_qt.addObject(o1);
	std::static_pointer_cast<QTO>(o1)->setPosition(sf::Vector2f(1000.f, 1000.f));
	//See what happens next
}
