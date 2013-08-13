#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"SFML/Graphics.hpp"

class GameObject
{
	enum ObjectType
	{
		PLAYER = 0,
		BULLET,
		ENEMY
	};
public:

	virtual void tick(sf::Time ticktime) = 0;
	virtual void collide(GameObject* pOther) = 0;
	
	virtual int getSubtype() const = 0;
	ObjectType getType() const;

	virtual void setPosition(sf::Vector2i position)= 0;
	virtual sf::Vector2i getSize() const = 0;
	virtual sf::Vector2i getPosition() const = 0;
	
	sf::IntRect getColRect() const;
	
	
	
protected:
	ObjectType m_type;
	int m_subtype;
	sf::IntRect m_colrect;
	sf::IntRect m_oldcolrect;
};
#endif