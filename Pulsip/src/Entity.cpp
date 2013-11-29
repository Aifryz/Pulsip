#include "../include/Entity.h"

void Entity::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(floor(position.x),floor(position.y));
	m_colrect.top = position.y;
	m_colrect.left = position.x;
}

void Entity::setSpeed(sf::Vector2f speed)
{
	m_speed = speed;
}

void Entity::addSpeed(sf::Vector2f speed)
{
	m_speed += speed;
}

sf::Vector2f Entity::getSpeed() const
{
	return m_speed;
}

sf::Vector2f Entity::getSize() const
{
	return sf::Vector2f(m_colrect.width,m_colrect.height);
}

sf::Vector2f Entity::getPosition() const
{
	return sf::Vector2f(m_colrect.left,m_colrect.top);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        target.draw(m_sprite, states);
}
