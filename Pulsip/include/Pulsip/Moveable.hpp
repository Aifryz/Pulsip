#ifndef PULSIP_MOVEABLE_HPP 
#define PULSIP_MOVEABLE_HPP
#include<SFML/System.hpp>
#include"Pulsip/Config.hpp"
namespace pul
{
	class Moveable
	{
	public:
		virtual ~Moveable(){};
		virtual sf::Vector2f getPosition() const = 0;
		virtual sf::Vector2f getVelocity() const { return m_velocity; }
		virtual sf::Vector2f getAcceleration() const { return m_acceleration; }

		virtual void tick(sf::Time dt) = 0;
		virtual void move(sf::Vector2f offset) = 0;
		virtual void move(float x, float y){ move(sf::Vector2f(x, y)); }
		virtual void setPosition(sf::Vector2f pos) = 0;
		virtual void setPosition(float x, float y){ setPosition(sf::Vector2f(x, y)); }

		virtual void setVelocity(sf::Vector2f velocity){ m_velocity = velocity; }
		virtual void setVelocity(float x, float y){ setVelocity(sf::Vector2f(x, y)); }
		virtual void addVelocity(sf::Vector2f velocity){ m_velocity += velocity; }
		virtual void addVelocity(float x, float y){ addVelocity(sf::Vector2f(x, y)); }

		virtual void setAcceleration(sf::Vector2f acceleration){ m_acceleration = acceleration; }
		virtual void setAcceleration(float x, float y){ setAcceleration(sf::Vector2f(x, y)); }
		virtual void addAcceleration(sf::Vector2f acceleration){ m_acceleration += acceleration; }
		virtual void addAcceleration(float x, float y){ addAcceleration(sf::Vector2f(x, y)); }
	protected:
		sf::Vector2f m_velocity;
		sf::Vector2f m_acceleration;
	};
}
#endif // !PULSIP_MOVEABLE_HPP
