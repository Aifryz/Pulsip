#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include"GameObject.h"
#include<list>
#include<algorithm>
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
	QuadTree(sf::Vector2i pos, sf::Vector2i size,int objectsToSplit = 3, int level = 0);
	QuadTree(sf::IntRect dims,int objectsToSplit = 3, int level = 0);
	QuadTree();
	~QuadTree();
	
	void addObject(GameObject* object);
	void removeObject(GameObject* object);
	std::list<GameObject*> getObjectsAt(sf::Vector2i pos);

	void removeEmpty();
	void draw(sf::RenderWindow* window);
	bool contains(sf::Vector2i pos);
private:

	void split();
	void addToLeaves();
	bool contains(GameObject* object);
	
	
	bool isLeaf;
	sf::IntRect dimensions;
	unsigned int objectsToSplit;
	unsigned int level;

	std::list<GameObject*> objects;
	QuadTree * 	nodes;
	
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

};
#endif // !QUAD_TREE_H
