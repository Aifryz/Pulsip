#include "../include/QuadTree.h"
#include <sstream>
#include <iostream>

QuadTree::QuadTree(sf::Vector2f pos, sf::Vector2f size,int objectsToSplit, int level)
{
	m_dimensions = sf::FloatRect(pos,size);
	m_objectsToSplit = objectsToSplit;
	m_level = 0;
	m_isLeaf = true;
	m_nodes = 0;
	m_total_objects = 0;
}

QuadTree::QuadTree(sf::FloatRect dims,int objectsToSplit, int level)
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
	m_dimensions = sf::FloatRect(0,0,0,0);
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

std::list<GameObject*> QuadTree::getObjectsAt(sf::Vector2i pos)
{
	if ( m_isLeaf ) {
		return m_objects;
	}

	std::list<GameObject*> returnedObjects;
	std::list<GameObject*> childObjects;

	if ( !m_objects.empty() )
		returnedObjects.insert( returnedObjects.end(), m_objects.begin(), m_objects.end() );

	for ( int n = 0; n < 4; ++n ) {
		if ( m_nodes[n].contains(pos) ) {
			childObjects = m_nodes[n].getObjectsAt( pos );
			returnedObjects.insert( returnedObjects.end(), childObjects.begin(), childObjects.end() );
			break;
		}
	}
	
	return returnedObjects;
}



//rmv empt

bool QuadTree::contains(sf::Vector2i pos)
{
	if ((pos.x > m_dimensions.left && pos.x < m_dimensions.left+m_dimensions.width)&&(pos.y>m_dimensions.top && pos.y < m_dimensions.top+m_dimensions.height))
		return true;
	return false;
}


//private:

void QuadTree::m_split()
{
	sf::Vector2f size(m_dimensions.width,m_dimensions.height);
	m_nodes = new QuadTree[4];
	m_nodes[NW] = QuadTree(sf::FloatRect(sf::Vector2f(m_dimensions.left,                   m_dimensions.top)                    ,size/2.f), m_objectsToSplit, m_level+1);
	m_nodes[NE] = QuadTree(sf::FloatRect(sf::Vector2f(m_dimensions.left+m_dimensions.width/2,m_dimensions.top)                    ,size/2.f), m_objectsToSplit, m_level+1);
	m_nodes[SW] = QuadTree(sf::FloatRect(sf::Vector2f(m_dimensions.left,                   m_dimensions.top+m_dimensions.height/2),size/2.f), m_objectsToSplit, m_level+1);
	m_nodes[SE] = QuadTree(sf::FloatRect(sf::Vector2f(m_dimensions.left+m_dimensions.width/2,m_dimensions.top+m_dimensions.height/2),size/2.f), m_objectsToSplit, m_level+1);
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
	sf::IntRect oRect = static_cast<sf::IntRect>( object->getColRect() );

	return(
        m_dimensions.left < oRect.left &&
        m_dimensions.top < oRect.top &&
        m_dimensions.top+m_dimensions.height > oRect.top+oRect.height &&
        m_dimensions.left+m_dimensions.width > oRect.left+oRect.width);
}
