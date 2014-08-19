#include"Pulsip/QuadTreeOccupant.hpp"
#include"Pulsip/QuadTreeNode.hpp"
namespace pul
{
	void QuadTreeOccupant::updatePositionInQuadTree()
	{
		if (!m_tree)//Object hasn't been added to tree
			return;
		m_tree->updateObject(this);
	}
}