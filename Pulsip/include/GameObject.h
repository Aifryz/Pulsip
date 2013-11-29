#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"SFML/Graphics.hpp"

class GameObject:public sf::Drawable
{
public:
	virtual void tick(sf::Time ticktime) = 0;
	virtual void collide(GameObject* other) = 0;//should be {other->onCollision(this))} in every derived object
	//collisions with every derived object
	//eg virtual void onCollision(Player* other) = 0;
	//add here

	virtual sf::Vector2f getSize() const = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual void setPosition(sf::Vector2i position)= 0;
	
	sf::FloatRect getColRect() const;
protected:
	sf::FloatRect m_colrect;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
#endif