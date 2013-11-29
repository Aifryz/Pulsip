#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "GameObject.h"
#include <list>
#include <algorithm>

class QuadTree
{
	enum Node
	{
	NW = 0,
	NE,
	SW,
	SE
	};

    public:
        QuadTree(sf::Vector2f pos, sf::Vector2f size,int objectsToSplit = 3, int level = 0);
        QuadTree(sf::FloatRect dims,int objectsTosplit = 3, int level = 0);
		QuadTree();
        ~QuadTree();
        
        void addObject(GameObject* object);
        void removeObject(GameObject* object);
        std::list<GameObject*> getObjectsAt(sf::Vector2i pos);

        void removeEmpty();
        bool contains(sf::Vector2i pos);

    private:
        void m_split();
        void m_addToLeaves();
        bool m_contains(GameObject* object);

        bool m_isLeaf;
        sf::FloatRect m_dimensions;
        unsigned int m_objectsToSplit;
        unsigned int m_level;
		unsigned int m_total_objects;

        std::list<GameObject*> m_objects;
        QuadTree* m_nodes;
};
#endif // !QUAD_TREE_H
