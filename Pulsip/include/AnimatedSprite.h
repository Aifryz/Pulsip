#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "SFML/Graphics.hpp"

//This class is heavily influenced by the sf::Sprite class
class AnimatedSprite:public sf::Transformable,public sf::Drawable
{
	
public:
	enum AnimationType
	{
		SINGLE_ROW = 0,
		MANUAL_ROW,
		WRAPPED_ROW
	};

	AnimatedSprite();
	AnimatedSprite(const sf::Texture& texture, sf::Vector2i framesize, AnimationType type);

	void setTexture(const sf::Texture& texture);
    void setColor(const sf::Color& color);

    const sf::Texture* getTexture() const;
    const sf::Color& getColor() const;

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

	void setFrame(int pos);
	void setRow(int pos);
	void setFrameDuration(sf::Time duration);
	
	sf::Time getFrameDuration() const;
	int getFrame() const;
	int getRow() const;

	void update();


	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void updatePositions();
    void updateTexCoords();

	sf::Vertex m_vertices[4];
    const sf::Texture* m_texture; 
    sf::IntRect m_textureRect;
	sf::Vector2i m_framesize;
	sf::Vector2i m_frameposition;
	sf::Vector2i m_frames;
	bool m_wrap_rows;

	
	sf::Time m_frameduration;
	sf::Clock m_updatetimer;
};
#endif
