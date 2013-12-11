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
		QuadTree(FloatRectangle dims,int objectsTosplit = 3, int level = 0);
		QuadTree();
        ~QuadTree();
        
        void addObject(GameObject* object);
        void removeObject(GameObject* object);
        std::list<GameObject*> getObjectsAt(sf::Vector2f pos);
		std::list<GameObject*> pollObjects(FloatRectangle area);
		std::list<GameObject*> getObjects();
		

        void removeEmpty();
        bool contains(sf::Vector2f pos);
		bool contains(GameObject* object);
		bool contains(FloatRectangle rect);
		bool intersects(FloatRectangle rect);
    private:
        void m_split();
        void m_addToLeaves();
        bool m_contains(GameObject* object);

        bool m_isLeaf;
        FloatRectangle m_dimensions;
        unsigned int m_objectsToSplit;
        unsigned int m_level;
		unsigned int m_total_objects;

        std::list<GameObject*> m_objects;
        QuadTree* m_nodes;
};
#endif // !QUAD_TREE_H
