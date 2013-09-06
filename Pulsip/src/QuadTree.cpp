#include "../include/QuadTree.h"
#include <sstream>
#include <iostream>

QuadTree::QuadTree(sf::Vector2i pos, sf::Vector2i size,int objectsToSplit, int level)
{
	dimensions = sf::IntRect(pos,size);
	this->objectsToSplit = objectsToSplit;
	this->level = 0;
	isLeaf = true;
	nodes = 0;	
}

QuadTree::QuadTree(sf::IntRect dims,int objectsToSplit, int level)
{
	dimensions = dims;
	this->objectsToSplit = objectsToSplit;
	this->level = level;
	isLeaf = true;
	nodes = 0;
}

QuadTree::QuadTree()
{
	dimensions = sf::IntRect(0,0,0,0);
	objectsToSplit = 3;
	level = 0;
	nodes = 0;
	isLeaf = true;
}

QuadTree::~QuadTree()
{
	if ( !isLeaf )
		delete [] nodes;
}

void QuadTree::addObject(GameObject* object)
{
	if(isLeaf)
	{
		objects.push_back(object);
		if(objects.size() == objectsToSplit)
		{
			split();
			addToLeaves();
			isLeaf = false;
		}
		return;
	}

	for(int n = 0;n<4;++n)
	{
		if (nodes[n].contains(object))
		{
			nodes[n].addObject(object);
			return;
		}
	}
	objects.push_back(object);
}
void QuadTree::removeObject(GameObject* object)
{
	if(!isLeaf)
	{
		for(int n = 0;n<4;++n)
		{
			if (nodes[n].contains(object))
			{
				nodes[n].removeObject( object );
				return;
			}
		}
	}

    auto i = objects.begin();
	for(; i != objects.end();)
			if (*i == object)
			{
				i = objects.erase(i);
				return;
			}
			else
				++i;
}

std::list<GameObject*> QuadTree::getObjectsAt(sf::Vector2i pos)
{
	if ( isLeaf ) {
		return objects;
	}

	std::list<GameObject*> returnedObjects;
	std::list<GameObject*> childObjects;

	if ( !objects.empty() )
		returnedObjects.insert( returnedObjects.end(), objects.begin(), objects.end() );

	for ( int n = 0; n < 4; ++n ) {
		if ( nodes[n].contains(pos) ) {
			childObjects = nodes[n].getObjectsAt( pos );
			returnedObjects.insert( returnedObjects.end(), childObjects.begin(), childObjects.end() );
			break;
		}
	}
	
	return returnedObjects;
}



//rmv empt

//draw
void QuadTree::draw(sf::RenderWindow* window)
{
	std::stringstream ss;
	ss<<objects.size();
	sf::String num = ss.str();

	
	
	text.setFont(font);
	text.setColor(sf::Color(255,0,64*(level-4)-1,255));
	text.setPosition(dimensions.left,dimensions.top+level*16);
	text.setCharacterSize(16);

	text.setString(num);
	
	window->draw(shape);
	window->draw(text);
	if(!isLeaf)
	{
		for (int n=0;n<4;++n)
		{
			nodes[n].draw(window);
		}
	}
}

bool QuadTree::contains(sf::Vector2i pos)
{
	if ((pos.x > dimensions.left && pos.x < dimensions.left+dimensions.width)&&(pos.y>dimensions.top && pos.y < dimensions.top+dimensions.height))
		return true;
	return false;
}


//private:

void QuadTree::split()
{
	sf::Vector2i size(dimensions.width,dimensions.height);
	nodes = new QuadTree[4];
	nodes[NW] = QuadTree(sf::IntRect(sf::Vector2i(dimensions.left,                   dimensions.top)                    ,size/2), objectsToSplit, level+1);
	nodes[NE] = QuadTree(sf::IntRect(sf::Vector2i(dimensions.left+dimensions.width/2,dimensions.top)                    ,size/2), objectsToSplit, level+1);
	nodes[SW] = QuadTree(sf::IntRect(sf::Vector2i(dimensions.left,                   dimensions.top+dimensions.height/2),size/2), objectsToSplit, level+1);
	nodes[SE] = QuadTree(sf::IntRect(sf::Vector2i(dimensions.left+dimensions.width/2,dimensions.top+dimensions.height/2),size/2), objectsToSplit, level+1);
}

//add to leaves
void QuadTree::addToLeaves()
{
	for (int n = 0; n < 4; ++n )
	{
		for(auto i = objects.begin(); i != objects.end();)
		{
			if(nodes[n].contains(*i))
			{
				nodes[n].addObject(*i);
				i = objects.erase(i);
			}
			else
				i++;
		}
	}

}


bool QuadTree::contains(GameObject* object)
{
	sf::IntRect oRect = object->getColRect();

	return(
        dimensions.left < oRect.left &&
        dimensions.top < oRect.top &&
        dimensions.top+dimensions.height > oRect.top+oRect.height &&
        dimensions.left+dimensions.width > oRect.left+oRect.width);
}
