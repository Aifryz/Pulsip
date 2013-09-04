#include "../include/Entity.h"

void Entity::setPosition(sf::Vector2i position)
{
	m_sprite.setPosition(position.x,position.y);
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

sf::Vector2i Entity::getSize() const
{
	return sf::Vector2i(m_colrect.width,m_colrect.height);
}

sf::Vector2i Entity::getPosition() const
{
	return static_cast<sf::Vector2i>(m_sprite.getPosition());
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        target.draw(m_sprite, states);
}
