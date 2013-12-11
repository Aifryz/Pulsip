#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"



class Player: public Entity
{
public:
	Player(const sf::Texture& texture);
	void tick(sf::Time ticktime);
	void collide(GameObject* pOther);
	void move(sf::Time time);

	int getSubtype() const;
	
private:
	void speedTick();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif