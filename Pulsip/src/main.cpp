#include "../include/Player.h"
#include "../include/ResourceManager.h"
//#include "../include/Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	ResourceManager man;
	
	sf::Clock clk;
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	Player p(man.getTexture("player.png"));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
        window.clear();
		sf::Time tt = clk.restart();
		p.move(tt);
		p.tick(tt);
		
		window.draw(p);
		window.draw(shape);
        window.display();
    }
	

    return 0;
}
