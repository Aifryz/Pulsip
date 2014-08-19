#include "Pulsip/QuadTree.hpp"
namespace pul{
	QuadTree::QuadTree(AABB area, int objectsToSplit)
	{
		m_root = std::make_shared<QuadTreeNode>(area, nullptr, objectsToSplit);
	}
	void QuadTree::addObject(QuadTreeOccupant::Ptr object)
	{
		m_root->addToChildren(object);
	}
	void QuadTree::removeObject(QuadTreeOccupant::Ptr object)
	{
		m_root->removeObject(object);
	}
	size_t QuadTree::size() const
	{
		return m_root->size();
	}
	std::shared_ptr<QuadTreeNode> QuadTree::getRoot()
	{
		return m_root;
	}
	void QuadTree::pollObjects(AABB area, std::vector<QuadTreeOccupant::Ptr>& returned_objects)
	{
		m_root->pollObjects(area, returned_objects);
	}
}
