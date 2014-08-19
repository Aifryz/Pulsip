#ifndef PULSIP_QUAD_TREE_NODE_HPP
#define PULSIP_QUAD_TREE_NODE_HPP
#include <vector>
#include "Pulsip/QuadTreeOccupant.hpp"
#include <Pulsip/Config.hpp>
namespace pul
{
	class PULSIP_API QuadTreeNode
	{
	public:
		enum Children
		{
			NW,
			NE,
			SW,
			SE,
			NUM_OF_CHILDREN
		};
		QuadTreeNode(sf::Vector2f pos, sf::Vector2f size, QuadTreeNode* parent = nullptr, int objectsToSplit = 3);
		QuadTreeNode(AABB dims, QuadTreeNode* parent = nullptr, int objectsToSplit = 3);
		QuadTreeNode();
		~QuadTreeNode();

		void removeObject(QuadTreeOccupant::Ptr object);
		void removeAllObjects();
		void getObjectsAt(sf::Vector2f pos, std::vector<QuadTreeOccupant::Ptr>& returned_objects);
		void pollObjects(AABB area, std::vector<QuadTreeOccupant::Ptr>& returned_objects);
		void getAllObjects(std::vector<QuadTreeOccupant::Ptr>& returned_objects);

		bool contains(sf::Vector2f pos);
		bool contains(QuadTreeOccupant::Ptr object);
		bool contains(AABB rect);
		bool intersects(AABB rect);
		size_t size();
		friend class QuadTree;
		friend class QuadTreeOccupant;
		QuadTreeNode* getChild(Children position);
		QuadTreeNode* getParent();
	private:
		void updateObject(QuadTreeOccupant* object);
		void addToChildren(QuadTreeOccupant::Ptr object);
		void addToParent(QuadTreeOccupant::Ptr object);
		void split();
		void shrink();
		bool addObjectToLeaves(size_t index);

		std::vector<QuadTreeOccupant::Ptr> m_objects;
		AABB m_aabb;
		QuadTreeNode* m_parent;
		QuadTreeNode* m_children;
		bool m_is_leaf;
		unsigned int m_objectsToSplit;
		unsigned int m_total_objects;
	};
}
#endif // !PULSIP_QUAD_TREE_NODE_HPP
