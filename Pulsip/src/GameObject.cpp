#include "..\include\GameObject.h"

sf::IntRect GameObject::getColRect() const
{
	return m_colrect;
}

GameObject::ObjectType GameObject::getType() const
{
	return m_type;
}
