#include "..\include\Player.h"

#include<iostream>

Player::Player(const sf::Texture& texture)
{
	m_sprite = AnimatedSprite(texture,sf::Vector2i(32,32),AnimatedSprite::MANUAL_ROW);
	m_sprite.setFrameDuration(sf::seconds(0.1));
	setPosition(sf::Vector2i(192,192));
	blocked = false;
	m_colrect.height = 31;
	m_colrect.width = 31;
	m_face = 0;
	
	

}

void Player::tick(sf::Time ticktime)
{
	speedTick();
	frameTick(ticktime);
	
	
	
}
void Player::collide(GameObject* pOther)
{
	
}
void Player::move(sf::Time time)
{
	m_oldcolrect = m_colrect;
	sf::Vector2f dp = (time.asSeconds()* m_speed) + m_rest;
	if(dp.x > 1 ||dp.x<-1 ||dp.y<-1 || dp.y > 1)
	{
		sf::Vector2i dpi = static_cast<sf::Vector2i>(dp);
		m_rest = dp - static_cast<sf::Vector2f>(dpi);
		dpi.x += m_colrect.left;
		dpi.y += m_colrect.top;
		setPosition(dpi);
	}
	else
		m_rest = dp;
	
}

int Player::getSubtype() const
{
	return 0;
}
void Player::speedTick()
{
	if(blocked)
	{
	m_colrect = m_oldcolrect;
	blocked = false;
	}

	
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
	
		
	m_sprite.setPosition(m_colrect.left,m_colrect.top);
}
void Player::frameTick(sf::Time time)
{
	sf::Vector2f dirspeed = m_speed/200.f;
	int x = (static_cast<int>(dirspeed.x)+1)*3;
	int y = static_cast<int>(dirspeed.y)+1;
	bool idle = false;
	switch (x+y)
	{
	case 0:
		m_face = 7;
		break;
	case 1:
		m_face = 6;
		break;
	case 2:
		m_face = 5;
		break;
	case 3:
		m_face = 0;
		break;
	case 4:
		idle = true;
		break;
	case 5:
		m_face = 4;
		break;
	case 6:
		m_face = 1;
		break;
	case 7:
		m_face = 2;
		break;
	case 8:
		m_face = 3;
		break;
	default:
		m_face = 0;//idle
		break;
	}
	

	m_sprite.setRow(m_face);
	m_sprite.update();
	
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//center the global view on player
	sf::View myview = target.getView();
	sf::Vector2f newcenter = static_cast<sf::Vector2f>(getPosition() + getSize()/2);
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

//bool contains(sf::FloatRect parent, sf::FloatRect child, sf::FloatRect& contained)
//{
//	bool istrue = (
//	parent.left < child.left &&
//	parent.top < child.top &&
//	parent.top+parent.height > child.top+child.height &&
//	parent.left+parent.width > child.left+child.width);
//	if(istrue)
//		contained = child;
//	else
//	{
//
//	}
//	NOT FINISHED!!!
//}
