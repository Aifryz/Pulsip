#ifndef UTIL_H
#define UTIL_H

#include "SFML/Graphics.hpp"
#include "../UtilTemplates.h"

/**Returns a vector witch you can use to eject first rectangle from the second one.
*(if you move the first rectangle by this vector it will no longer intersect the second one)
*/
sf::Vector2i getCollisionVector(sf::IntRect first, sf::IntRect second);

#endif // !UTIL_H
