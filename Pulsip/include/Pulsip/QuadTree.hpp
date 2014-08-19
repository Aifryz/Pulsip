#ifndef PULSIP_QUAD_TREE_HPP
#define PULSIP_QUAD_TREE_HPP
#include"Pulsip/QuadTreeNode.hpp"
namespace pul
{
	class PULSIP_API QuadTree
	{
	public:
		QuadTree(AABB area, int objectsToSplit = 3);
		void addObject(QuadTreeOccupant::Ptr object);
		void removeObject(QuadTreeOccupant::Ptr object);
		size_t size() const;
		std::shared_ptr<QuadTreeNode> getRoot();
		void pollObjects(AABB area, std::vector<QuadTreeOccupant::Ptr>& returned_objects);
	private:
		std::shared_ptr<QuadTreeNode> m_root;
		
	};
}
#endif // !PULSIP_QUAD_TREE_HPP
