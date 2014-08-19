#include"Pulsip/QuadTreeNode.hpp"
#include"Pulsip/Util.hpp"
namespace pul
{
	QuadTreeNode::QuadTreeNode(sf::Vector2f pos, sf::Vector2f size, QuadTreeNode* parent, int objectsToSplit):
		QuadTreeNode(AABB(pos,size),parent,objectsToSplit)
	{}
	QuadTreeNode::QuadTreeNode(AABB dims, QuadTreeNode* parent, int objectsToSplit) :
		m_aabb(dims),
		m_parent(parent),
		m_objectsToSplit(objectsToSplit),
		m_is_leaf(true),
		m_children(nullptr),
		m_total_objects(0)
	{}
	QuadTreeNode::QuadTreeNode()
	{}
	QuadTreeNode::~QuadTreeNode()
	{
		if (!m_is_leaf)
		{
			delete[] m_children;
		}
	}
	void QuadTreeNode::addToChildren(QuadTreeOccupant::Ptr object)
	{
		m_total_objects++;
		if (m_is_leaf)//no children, add to this tree
		{
			object->m_tree = this;
			m_objects.push_back(object);
			if (m_objects.size() >= m_objectsToSplit)
			{
				split();
				m_is_leaf = false;
			}
			return;
		}
		for(int n = 0; n<4; n++)
		{
			if (m_children[n].contains(object))
			{
				m_children[n].addToChildren(object);
				return;
			}
		}
		//hasn't been added to children, add to this tree
		object->m_tree = this;
		m_objects.push_back(object);
	}
	void QuadTreeNode::addToParent(QuadTreeOccupant::Ptr object)
	{
		m_total_objects--;
		if (m_aabb.contains(object->getAABB()))
		{
			addToChildren(object);
		}
		else
		{
			if (m_parent)
				m_parent->addToParent(object);
		}
	}
	void QuadTreeNode::updateObject(QuadTreeOccupant* object)
	{
		QuadTreeOccupant::Ptr cur;
		size_t i;
		for (i = 0; i < m_objects.size(); i++)//possible bootleneck?
		{
			if (m_objects[i].get() == object)
			{
				cur = m_objects[i];
				break;
			}
		}
		const AABB& aabb = object->getAABB();
		if (m_aabb.contains(aabb))
		{
			m_total_objects--;//Balances out the m_total_objects++ at the beginning of addToChildren(). If object already lies in tree, the object count is the same
			addToChildren(cur);
		}
		else
		{
			//remove from this tree and add to parent
			cur->m_tree = nullptr;
			pul::fastErase(m_objects,i);
			addToParent(cur);
		}
	}
	void QuadTreeNode::removeObject(QuadTreeOccupant::Ptr object)
	{
		if (!m_is_leaf)
		{
			for (int n = 0; n<4; ++n)
			{
				if (m_children[n].contains(object))
				{
					m_children[n].removeObject(object);
					m_total_objects--;
					return;
				}
			}
		}
		for (size_t i = 0; i < m_objects.size(); i++)
		{
			if (m_objects[i] == object)
			{
				m_objects[i]->m_tree = nullptr;
				pul::fastErase(m_objects, i);
				m_total_objects--;
				return;
			}
		}
	}
	void QuadTreeNode::removeAllObjects()
	{
		if (!m_is_leaf)
		{
			for (int i = 0; i < 4; i++)//remove objects in leaves 
			{
				m_children->removeAllObjects();
			}
		}
		for (size_t i = 0; i < m_objects.size(); i++)
		{
			m_objects[i]->m_tree = nullptr;
		}
		m_objects.clear();
	}
	void QuadTreeNode::getObjectsAt(sf::Vector2f pos, std::vector<QuadTreeOccupant::Ptr>& returned_objects)
	{
		returned_objects.insert(returned_objects.end(), m_objects.begin(), m_objects.end());
		if (m_is_leaf)
		{
			return;
		}
		for (int n = 0; n < 4; ++n)
		{
			if (m_children[n].contains(pos))
			{
				m_children[n].getObjectsAt(pos, returned_objects);
				return;
			}
		}
	}
	void QuadTreeNode::pollObjects(AABB area, std::vector<QuadTreeOccupant::Ptr>& returned_objects)
	{
		returned_objects.insert(returned_objects.end(), m_objects.begin(), m_objects.end());
		if (m_is_leaf)
		{
			return;
		}
		for (int n = 0; n < 4; ++n)
		{
			if (m_children[n].intersects(area))
			{
				m_children[n].pollObjects(area, returned_objects);
			}
		}
	}
	void QuadTreeNode::getAllObjects(std::vector<QuadTreeOccupant::Ptr>& returned_objects)
	{
		returned_objects.insert(returned_objects.end(), m_objects.begin(), m_objects.end());
		if (m_is_leaf)
		{
			return;
		}
		for (int n = 0; n < 4; ++n)
		{
			m_children[n].getAllObjects(returned_objects);
		}
	}

	bool QuadTreeNode::contains(sf::Vector2f pos)
	{
		return m_aabb.contains(pos);
	}
	bool QuadTreeNode::contains(QuadTreeOccupant::Ptr object)
	{
		return m_aabb.contains(object->getAABB());
	}
	bool QuadTreeNode::contains(AABB rect)
	{
		return m_aabb.contains(rect);
	}
	bool QuadTreeNode::intersects(AABB rect)
	{
		return m_aabb.intersects(rect);
	}
	size_t QuadTreeNode::size()
	{
		return m_total_objects;
	}
	void QuadTreeNode::split()
	{
		const sf::Vector2f& halfsize = m_aabb.getHalfSize();
		m_children = new QuadTreeNode[4];
		m_children[NW] = QuadTreeNode(AABB(m_aabb.getPosition() + sf::Vector2f(-halfsize.x, -halfsize.y) / 2.f, halfsize), this, m_objectsToSplit);
		m_children[NE] = QuadTreeNode(AABB(m_aabb.getPosition() + sf::Vector2f(halfsize.x, -halfsize.y) / 2.f, halfsize), this, m_objectsToSplit);
		m_children[SW] = QuadTreeNode(AABB(m_aabb.getPosition() + sf::Vector2f(-halfsize.x, halfsize.y) / 2.f, halfsize), this, m_objectsToSplit);
		m_children[SE] = QuadTreeNode(AABB(m_aabb.getPosition() + sf::Vector2f(halfsize.x, halfsize.y) / 2.f, halfsize), this, m_objectsToSplit);
		for (size_t i = 0; i < m_objects.size();)
		{
			if (!addObjectToLeaves(i))
				i++;
		}
	}
	void QuadTreeNode::shrink()
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_children[4].getAllObjects(m_objects);
		}
		delete[] m_children;
		m_children = nullptr;
	}
	bool QuadTreeNode::addObjectToLeaves(size_t index)
	{
		for (size_t n = 0; n < NUM_OF_CHILDREN; n++)
		{
			if (m_children[n].contains(m_objects[index]))
			{
				m_children[n].addToChildren(m_objects[index]);
				fastErase(m_objects, index);
				return true;
			}
		}
		return false;
	}
	QuadTreeNode* QuadTreeNode::getChild(Children position)
	{
		if (!m_is_leaf)
		{
			return &m_children[position];
		}
		else return nullptr;
	}
	QuadTreeNode* QuadTreeNode::getParent()
	{
		return m_parent;
	}
}