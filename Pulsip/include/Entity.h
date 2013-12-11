#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"

class Entity:public GameObject
{
    public:
        virtual void tick(sf::Time ticktime) = 0;
        virtual void collide(GameObject* pOther) = 0;
        virtual void move(sf::Time time) = 0;

        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition() const;

        void setSpeed(sf::Vector2f speed);
        void addSpeed(sf::Vector2f speed);
        sf::Vector2f getSpeed() const;

        sf::Vector2f getSize() const;
        virtual int getSubtype() const = 0;

    protected:
        sf::Vector2f m_speed;
		sf::Sprite m_sprite;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
#endif
