#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"



class Player: public Entity
{
public:
	Player(const sf::Texture& texture);
	Player(){};
	void tick(sf::Time ticktime);
	void collide(GameObject* pOther);
	void move(sf::Time time);

	int getSubtype() const;
	
private:
	sf::Time m_frametime;
	sf::Time m_dirtime;
	void speedTick();
	void frameTick(sf::Time time);
	char m_frame;
	char m_face;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//facing
	//812  
	//7X3
	//654
	

};
#endif