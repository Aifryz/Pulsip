#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H

#include"SFML/Graphics.hpp"
#include<vector>
#include<map>
struct Frame
{
	sf::IntRect framerect;
	sf::Time duration;
};
/** Animation that can be animated inside SpriteAnimator*/
class SpriteAnimation
{
public:
	SpriteAnimation();
	sf::IntRect update(sf::Time dt);
	bool isLastFrame();
	void addFrame(Frame frame);
	void restart();
private:
	sf::Time m_elapsedtime;
	std::vector<Frame> m_frames;
	unsigned int m_framepos;
};
/**Main SpriteAnimator Class*/
class SpriteAnimator
{
public:
	SpriteAnimator(sf::Sprite& sprite);

	bool start(std::string name,bool loop = false);
	bool stop();
	bool restart();
	void addAnimation(SpriteAnimation anim, std::string name);
	bool isplayinganimation();
	void update(sf::Time dt);
private:
	std::string m_currrent;
	bool m_loop;
	sf::Sprite& m_sprite;
	std::map<std::string,SpriteAnimation> m_animations;
};
/**Helper function to add multiple frames to single animation*/
void addFrames(SpriteAnimation& animation, int row, int start, int stop, sf::Vector2i framesize);

#endif // !SPRITE_ANIMATOR_H
