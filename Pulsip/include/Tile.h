#ifndef TILE_H
#define TILE_H

#include"SFML/Graphics.hpp"

class Tile
{
    public:
        enum SubType
        {
            FLOOR = 0,
            WALL,
            GRATE
        };

        Tile(int subtype, int x, int y);
        Tile();
        void tick(sf::Time ticktime);

        sf::Vector2i getSize() const;
        sf::Vector2i getPosition() const;

        int getType() const;
        bool isCollideable() const;
		bool intersects(sf::Vector2i p1, sf::Vector2i p2) const;

    private:
        sf::Vector2i m_position;
        sf::Vector2i m_size;
        int m_type;
};

#endif
