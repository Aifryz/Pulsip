#include"../include/SpriteAnimator.h"

SpriteAnimation::SpriteAnimation()
{
	m_framepos =0;
}
sf::IntRect SpriteAnimation::update(sf::Time dt)
{
	m_elapsedtime += dt;
	if(m_elapsedtime >= m_frames[m_framepos].duration)
	{
		m_framepos++;
		m_elapsedtime = sf::seconds(0);
		if(m_framepos>=m_frames.size())
			m_framepos=0;
			
	}
	return m_frames[m_framepos].framerect;
}
void SpriteAnimation::addFrame(Frame frame)
{
	m_frames.push_back(frame);
}
void SpriteAnimation::restart()
{
	m_framepos = 0;
	m_elapsedtime = sf::seconds(0);
}
bool SpriteAnimation::isLastFrame()
{
	if(m_framepos == m_frames.size()-1)
		return true;
	return false;
}
///////////////////////
SpriteAnimator::SpriteAnimator(sf::Sprite& sprite):
	m_sprite(sprite)
{
	m_loop = false;
	m_currrent = "";
}
void SpriteAnimator::addAnimation(SpriteAnimation anim, std::string name)
{
	m_animations[name] = anim;
}
bool SpriteAnimator::start(std::string name,bool loop)
{
	if(m_animations.find(name) == m_animations.end())
		return false;
	m_loop = loop;
	m_currrent = name;
	return true;
}
bool SpriteAnimator::stop()
{
	if(m_currrent == "")
		return false;

	m_animations[m_currrent].restart();
	m_currrent = "";
	return true;
}
bool SpriteAnimator::restart()
{
	if(m_currrent == "")
		return false;
	m_animations[m_currrent].restart();
	return true;
}
bool SpriteAnimator::isplayinganimation()
{
	if(m_currrent == "")
		return false;
	return true;
}
void SpriteAnimator::update(sf::Time dt)
{
	if(m_currrent == "")
		return;

	sf::IntRect newrect = m_animations[m_currrent].update(dt);
	m_sprite.setTextureRect(newrect);

	if(m_animations[m_currrent].isLastFrame() && !m_loop)
		m_currrent = "";

}

