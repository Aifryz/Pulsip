#include "../include/Player.h"
#include "../include/ResourceManager.h"
#include "../include/Game.h"
#include "../include/SpriteAnimator.h"
#include "../include/util.h"
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	ResourceManager man;
	sf::Clock clk;
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	//static second
	sf::RectangleShape stat(sf::Vector2f(50,50));
	stat.setPosition(100,100);
	stat.setFillColor(sf::Color::Blue);
	
	//first
	sf::RectangleShape first(sf::Vector2f(30,30));
	first.setPosition(100,100);
	first.setFillColor(sf::Color::Red);
	sf::IntRect f(10,10,50,50);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		first.setPosition(pos.x,pos.y);
		
			
		
        window.clear();
		sf::Vector2i dir = getCollisionVector(static_cast<sf::IntRect>(first.getGlobalBounds()),static_cast<sf::IntRect>(stat.getGlobalBounds()));
		std::cout<<"x: "<<dir.x<<" y: "<<dir.y<<"\n";
		sf::Time tt = clk.restart();
		window.draw(stat);
		window.draw(first);
        window.display();
    }
	

    return 0;
}
