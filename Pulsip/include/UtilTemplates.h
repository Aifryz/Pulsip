#ifndef UTIL_TEMPLATES_H
#define UTIL_TEMPLATES_H

#include "SFML/Graphics.hpp"
/**This file contains some utility templates*/

/**Returns vector that contains signs of inputed vector*/
template<typename T>
sf::Vector2<T> getSignVector(sf::Vector2<T> vector)
{
	sf::Vector2<T> sign;

	sign.x = (vector.x < 0)? -1 : 1;
	sign.y = (vector.y < 0)? -1 : 1;

	sign.x = (vector.x == 0)? 0 : sign.x;
	sign.y = (vector.y == 0)? 0 : sign.y;

	return sign;
}
#endif // !UTIL_TEMPLATES_H
