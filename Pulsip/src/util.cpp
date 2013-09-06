#include "../include/util.h"
sf::Vector2i getCollisionVector(sf::IntRect first, sf::IntRect second)
{
	
	sf::Vector2i firsthalfsize = sf::Vector2i(first.width/2 , first.height/2);
	sf::Vector2i secondhalfsize = sf::Vector2i(second.width/2 , second.height/2);

	sf::Vector2i distance = getCenter(first)-getCenter(second);
	sf::Vector2i sign = getSignVector(distance);
	sf::Vector2i absdistance(abs(distance.x),abs(distance.y));

	sf::Vector2i difference = (firsthalfsize+secondhalfsize)-absdistance;
	
	if(difference.x>0 && difference.y>0)//we check if there's collision on both axis
	{
		if(difference.x<difference.y)
		{
			return sf::Vector2i(sign.x*difference.x,0);
		}
		else
		{
			return sf::Vector2i(0,sign.y*difference.y);
		}
	}
	return sf::Vector2<int>(0,0);//return zero-vector if there's no collision
}