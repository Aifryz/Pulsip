
#include "../include/Player.h"
#include "../include/ResourceManager.h"
#include "../include/Game.h"
#include "../include/SpriteAnimator.h"
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	ResourceManager man;
	
	sf::Clock clk;
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	sf::Sprite spr(man.getTexture("player.png"));
	Frame frame1;
	frame1.duration = sf::milliseconds(500);
	frame1.framerect = sf::IntRect(0,0,32,32);

	Frame frame2;
	Frame frame3;

	frame2.duration = sf::milliseconds(500);
	frame2.framerect = sf::IntRect(32,0,32,32);
	std::cout<<frame1.framerect.height;
	SpriteAnimation anim;
	anim.addFrame(frame1);
	anim.addFrame(frame2);
	
	SpriteAnimator animator(spr);
	animator.addAnimation(anim,"pie");
	animator.start("pie",false);
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
		animator.update(tt);
		window.draw(spr);
		//window.draw(shape);
        window.display();
    }
	

    return 0;
}