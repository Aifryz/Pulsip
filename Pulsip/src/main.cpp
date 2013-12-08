#include <iostream>
#include "SFML/Graphics.hpp"
#include "../include/TileMap.h"
#include "../include/GameObject.h"
//class Sim:public GameObject
//{
//public:
//	Sim()
//	{
//		m_colrect = sf::FloatRect(0,0,33,33);
//		drawrect = sf::RectangleShape(getSize());
//		drawrect.setPosition(getPosition());
//		drawrect.setFillColor(sf::Color::Transparent);
//		drawrect.setOutlineThickness(1.0);
//		drawrect.setOutlineColor(sf::Color::Green);
//		
//	}
//	virtual void tick(sf::Time ticktime){};
//	virtual void collide(GameObject* other){};//should be {other->onCollision(this))} in every derived object
//	//collisions with every derived object
//	//eg virtual void onCollision(Player* other) = 0;
//	//add here
//
//	virtual sf::Vector2f getSize() const
//	{
//		return sf::Vector2f(m_colrect.width,m_colrect.height);
//	}
//	virtual sf::Vector2f getPosition() const
//	{
//		return sf::Vector2f(m_colrect.left, m_colrect.top);
//	}
//	virtual void setPosition(sf::Vector2i position)
//	{
//		m_colrect.left = position.x;
//		m_colrect.top = position.y;
//		drawrect.setPosition(static_cast<sf::Vector2f>(position));
//	}
//	
//	sf::FloatRect getColRect() const;
//protected:
//	//sf::FloatRect m_colrect;
//	sf::RectangleShape drawrect;
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
//	{
//		target.draw(drawrect);
//	}
//
//};
int main()
{
	//classes
	//-rectangle
	//-rectangle area
	//-
	//drawing
	//colideable green
	//non col black with white border
	//line blue
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	sf::Vector2f p1(400,300);
	sf::Vector2f p2(0,0);
	sf::VertexArray arr;
	arr.append(sf::Vertex(p1,sf::Color(0,0,255)));
	arr.append(sf::Vertex(p2,sf::Color(0,0,255)));
	arr.setPrimitiveType(sf::Lines);
	sf::Texture maptex;
	sf::Texture sprtx;
	sprtx.loadFromFile("cross.png");
	maptex.loadFromFile("tileset.png");
	
	
	sf::Clock clk;
	TileMap tlm(&maptex);
	sf::Vector2i p3(160,113);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		//float z = (p2.y-p1.y)*pos.x + (p1.x-p2.x)*pos.y + (p2.x*p1.y-p1.x*p2.y);
		//std::cout<<pos.x<<" "<<pos.y<<" "<<z<<"\n";
		//float z = (p2.y-p1.y)*pos.x + (p1.x-p2.x)*pos.y + (p2.x*p1.y-p1.x*p2.y);
		//std::vector<Tile> tiles = tlm.getCollidingWith(&test);
		sf::Time start = clk.getElapsedTime();
		std::vector<Tile> tiles = tlm.getCollidingWith(static_cast<sf::Vector2i>(p1),pos);
		sf::Time mid = clk.getElapsedTime();
		std::vector<Tile> tiles2 = tlm.getCollidingWithDbg(static_cast<sf::Vector2i>(p1),pos);
		sf::Time stop = clk.getElapsedTime();
		arr[1].position = static_cast<sf::Vector2f>(pos);
		std::cout<<"dbg "<<mid.asMicroseconds()-stop.asMicroseconds()<<"\n";
		std::cout<<"std "<<start.asMicroseconds()-mid.asMicroseconds()<<"\n";
		if(mid.asMicroseconds()-stop.asMicroseconds() > start.asMicroseconds()-mid.asMicroseconds())
		{
			std::cout<<"ssssssssssssssssssssssssssssssssssssssssssssssssss"<<"\n";
		}
		std::vector<sf::Sprite> sprs;
		
        window.clear();
		
		window.draw(tlm);
		for(Tile tl :tiles)
		{
			sf::Sprite spr(sprtx);
			spr.setPosition(static_cast<sf::Vector2f>(tl.getPosition()));
			window.draw(spr);
		}
		window.draw(arr);
		//window.draw(test);
        window.display();
    }

	return 0;
}


