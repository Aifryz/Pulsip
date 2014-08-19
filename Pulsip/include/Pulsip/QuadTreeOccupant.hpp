#ifndef PULSIP_QUAD_TREE_OCCUPANT_HPP
#define PULSIP_QUAD_TREE_OCCUPANT_HPP
#include<memory>
#include"Pulsip/Rectangle.hpp"
#include"Pulsip/Config.hpp"
namespace pul
{
	//forward declaration
	class QuadTreeNode;
	///Class representing object lying inside of QuadTree
	class PULSIP_API QuadTreeOccupant
	{
	public:
		QuadTreeOccupant()
		{
			m_tree = nullptr;
		}
		virtual ~QuadTreeOccupant(){}
		///Has to return const ref to AABB, QuadTree uses this AABB to determine where given object lies
		virtual const AABB& getAABB() = 0;
		///This method updates position of object in quadtree
		virtual void updatePositionInQuadTree();
		typedef std::shared_ptr<QuadTreeOccupant> Ptr;
		friend class QuadTreeNode;
	private:
		///QuadTree which contains the object 
		QuadTreeNode* m_tree;
		
	};
}
#endif // !PULSIP_QUAD_TREE_OCCUPANT_HPP
