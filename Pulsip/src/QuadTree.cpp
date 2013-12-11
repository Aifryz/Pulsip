#include "../include/QuadTree.h"
#include <sstream>
#include <iostream>

QuadTree::QuadTree(sf::Vector2f pos, sf::Vector2f size,int objectsToSplit, int level)
{
	m_dimensions = FloatRectangle(size,pos);
	m_objectsToSplit = objectsToSplit;
	m_level = 0;
	m_isLeaf = true;
	m_nodes = 0;
	m_total_objects = 0;
}

QuadTree::QuadTree(FloatRectangle dims,int objectsToSplit, int level)
{
	m_dimensions = dims;
	m_objectsToSplit = objectsToSplit;
	m_level = level;
	m_isLeaf = true;
	m_nodes = 0;
	m_total_objects = 0;
}

QuadTree::QuadTree()
{
	m_dimensions = FloatRectangle(0,0,0,0);
	m_objectsToSplit = 3;
	m_level = 0;
	m_nodes = 0;
	m_isLeaf = true;
	m_total_objects = 0;
}

QuadTree::~QuadTree()
{
	if ( !m_isLeaf )
		delete [] m_nodes;
}

void QuadTree::addObject(GameObject* object)
{
	m_total_objects++;
	if(m_isLeaf)
	{
		m_objects.push_back(object);
		if(m_objects.size() == m_objectsToSplit)
		{
			m_split();
			m_addToLeaves();
			m_isLeaf = false;
		}
		return;
	}

	for(int n = 0;n<4;++n)
	{
		if (m_nodes[n].m_contains(object))
		{
			m_nodes[n].addObject(object);
			return;
		}
	}
	m_objects.push_back(object);
}
void QuadTree::removeObject(GameObject* object)
{
	m_total_objects--;
	if(!m_isLeaf)
	{
		for(int n = 0;n<4;++n)
		{
			if (m_nodes[n].m_contains(object))
			{
				m_nodes[n].removeObject( object );
				return;
			}
		}
	}

    auto i = m_objects.begin();
	for(; i != m_objects.end();)
			if (*i == object)
			{
				i = m_objects.erase(i);
				return;
			}
			else
				++i;
}

std::list<GameObject*> QuadTree::getObjectsAt(sf::Vector2f pos)
{
	if ( m_isLeaf ) {
		return m_objects;
	}

	std::list<GameObject*> returnedObjects;
	std::list<GameObject*> childObjects;

	if ( !m_objects.empty() )
		returnedObjects.insert( returnedObjects.end(), m_objects.begin(), m_objects.end() );

	for ( int n = 0; n < 4; ++n )
	{
		if ( m_nodes[n].contains(pos) )
		{
			childObjects = m_nodes[n].getObjectsAt( pos );
			returnedObjects.insert( returnedObjects.end(), childObjects.begin(), childObjects.end() );
			break;
		}
	}
	
	return returnedObjects;
}
std::list<GameObject*> QuadTree::getObjects()
{
	return m_objects;
}
std::list<GameObject*> QuadTree::pollObjects(FloatRectangle area)
{
	if ( m_isLeaf ) {
		return m_objects;
	}
	std::list<GameObject*> returnedObjects;
	std::list<GameObject*> childObjects;
	if ( !m_objects.empty() )
		returnedObjects.insert( returnedObjects.end(), m_objects.begin(), m_objects.end() );
	for (int i = 0; i < 4; i++)
	{
		if(m_nodes[i].intersects(area))
		{
			childObjects = m_nodes[i].pollObjects(area);
			returnedObjects.insert( returnedObjects.end(), childObjects.begin(), childObjects.end() );
		}
	}
}

//rmv empt

bool QuadTree::contains(sf::Vector2f pos)
{
	return m_dimensions.contains(pos);
}

bool QuadTree::intersects(FloatRectangle rect)
{
	return m_dimensions.intersects(rect);
}
bool QuadTree::contains(FloatRectangle rect)
{
	return m_dimensions.contains(rect);
}
///////////private:

void QuadTree::m_split()
{
	sf::Vector2f halfsize = m_dimensions.getHalfSize();
	m_nodes = new QuadTree[4];
	m_nodes[NW] = QuadTree(FloatRectangle(m_dimensions.getPosition()+sf::Vector2f(-halfsize.x, -halfsize.y),halfsize), m_objectsToSplit, m_level+1);
	m_nodes[NE] = QuadTree(FloatRectangle(m_dimensions.getPosition()+sf::Vector2f(halfsize.x, -halfsize.y ),halfsize), m_objectsToSplit, m_level+1);
	m_nodes[SW] = QuadTree(FloatRectangle(m_dimensions.getPosition()+sf::Vector2f(-halfsize.x, halfsize.y),halfsize), m_objectsToSplit, m_level+1);
	m_nodes[SE] = QuadTree(FloatRectangle(m_dimensions.getPosition()+sf::Vector2f(halfsize.x,halfsize.y),halfsize), m_objectsToSplit, m_level+1);
}

//add to leaves
void QuadTree::m_addToLeaves()
{
	for (int n = 0; n < 4; ++n )
	{
		for(auto i = m_objects.begin(); i != m_objects.end();)
		{
			if(m_nodes[n].m_contains(*i))
			{
				m_nodes[n].addObject(*i);
				i = m_objects.erase(i);
			}
			else
				i++;
		}
	}

}


bool QuadTree::m_contains(GameObject* object)
{
	return(m_dimensions.contains(object->getAABB()));
}

