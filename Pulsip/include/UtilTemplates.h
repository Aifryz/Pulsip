#ifndef UTIL_TEMPLATES_H
#define UTIL_TEMPLATES_H

#include "SFML/Graphics.hpp"
/**This file contains some utility templates*/

/**Calculates the right border of the rect*/
template<typename T>
inline T right(sf::Rect<T> rect)
{
	return rect.left+rect.width;
}

/**Calculates the bottom border of the rect*/
template<typename T>
inline T bottom(sf::Rect<T> rect)
{
	return rect.top+rect.height;
}

/**Calculates the center of the rect*/
template<typename T>
inline sf::Vector2<T> getCenter(sf::Rect<T> rect)
{
	return sf::Vector2<T>(rect.left + rect.width/2, rect.top + rect.height/2);
}

/**Returns vector that contains signs of inputed vector*/
template<typename T>
sf::Vector2<T> getSignVector(sf::Vector2<T> vector)
{
	sf::Vector2<T> sign;

	sign.x = (vector.x < 0)? -1 : 1;
	sign.y = (vector.y < 0)? -1 : 1;

	sign.x = (vector.x == 0)? 0 : signx;
	sign.y = (vector.y == 0)? 0 : signy;

	return sign;
}

/**Returns dot product of two vectors*/
template<typename T>
inline T dotProduct(sf::Vector2<T> first , sf::Vector2<T> second)
{
	T first.x*second.x + first.y*second.y;
}
#endif // !UTIL_TEMPLATES_H
