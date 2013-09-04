#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"
#include "AnimatedSprite.h"

class Entity:public sf::Drawable,public GameObject
{
    public:
        virtual void tick(sf::Time ticktime) = 0;
        virtual void collide(GameObject* pOther) = 0;
        virtual void move(sf::Time time) = 0;

        void setPosition(sf::Vector2i position);
        sf::Vector2i getPosition() const;

        void setSpeed(sf::Vector2f speed);
        void addSpeed(sf::Vector2f speed);
        sf::Vector2f getSpeed() const;

        sf::Vector2i getSize() const;
        virtual int getSubtype() const = 0;
        bool destroyed;
        bool blocked;

    protected:
        sf::Vector2f m_speed;
        sf::Vector2f m_rest;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
        
        AnimatedSprite m_sprite;
};
#endif
