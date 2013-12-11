#include "../include/Player.h"
#include <iostream>

Player::Player(const sf::Texture& texture)
{
	m_sprite = sf::Sprite(texture);
}

void Player::tick(sf::Time ticktime)
{
	speedTick();
}
void Player::collide(GameObject* pOther)
{
	
}
void Player::move(sf::Time time)
{
	sf::Vector2f dp = time.asSeconds()* m_speed;
	m_AABB.setPosition(m_AABB.getPosition()+dp);
	m_sprite.setPosition(floor(m_AABB.getPosition().x),floor(m_AABB.getPosition().y));
}

int Player::getSubtype() const
{
	return 0;
}
void Player::speedTick()
{
	setSpeed(sf::Vector2f(0,0));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		addSpeed(sf::Vector2f(0,-200));
		//std::cout<<"W";
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		addSpeed(sf::Vector2f(0,200));
		//std::cout<<"S";
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		addSpeed(sf::Vector2f(-200,0));
		//std::cout<<"A";
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		addSpeed(sf::Vector2f(200,0));
		//std::cout<<"D";
	}
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//draw player
	target.draw(m_sprite, states);
}
