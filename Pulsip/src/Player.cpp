#include "../include/Player.h"
#include <iostream>

Player::Player(const sf::Texture& texture)
{
	m_sprite = sf::Sprite(texture);
	setPosition(sf::Vector2f(192.f,192.f));
	m_colrect.height = 31.f;
	m_colrect.width = 31.f;
	

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
	m_colrect.top += dp.y;
	m_colrect.left += dp.x;

	m_sprite.setPosition(floor(m_colrect.left),floor(m_colrect.top));
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
	//center the global view on player
	sf::View myview = target.getView();
	sf::Vector2f newcenter = getPosition() + getSize()/2.f;
	myview.setCenter(newcenter);
	target.setView(myview);

	//draw player
	target.draw(m_sprite, states);
}

bool contains(sf::FloatRect parent, sf::FloatRect child)
{
	bool istrue = (
	parent.left < child.left &&
	parent.top < child.top &&
	parent.top+parent.height > child.top+child.height &&
	parent.left+parent.width > child.left+child.width);
	return istrue;
}
