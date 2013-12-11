#include "../include/Entity.h"

void Entity::setPosition(sf::Vector2f position)
{
	m_AABB.setPosition(position);
	m_sprite.setOrigin(m_AABB.getHalfSize());
	m_sprite.setPosition(floor(position.x),floor(position.y));
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
	return m_AABB.getSize();
}

sf::Vector2f Entity::getPosition() const
{
	return m_AABB.getPosition();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
