#include"..\include\AnimatedSprite.h"
AnimatedSprite::AnimatedSprite()
{
	m_texture = NULL;
	m_textureRect = sf::IntRect();
}
AnimatedSprite::AnimatedSprite(const sf::Texture& texture, sf::Vector2i framesize, AnimatedSprite::AnimationType type)
{
	setTexture(texture);
	m_framesize = framesize;
	m_frameposition = sf::Vector2i(0,0);
	sf::Vector2i pos(m_frameposition.x*m_framesize.x,m_frameposition.y*m_framesize.y);
	m_textureRect = sf::IntRect(pos, m_framesize);
	m_updatetimer.restart();
	
	switch (type)
	{
	case AnimatedSprite::SINGLE_ROW:
		m_frames = sf::Vector2i(texture.getSize().x/framesize.x,1);
		m_wrap_rows = false;
		break;
	case AnimatedSprite::MANUAL_ROW:
		m_frames = sf::Vector2i(texture.getSize().x/framesize.x,texture.getSize().y/framesize.y);
		
		m_wrap_rows = false;
		break;
	case AnimatedSprite::WRAPPED_ROW:
		m_frames = sf::Vector2i(texture.getSize().x/framesize.x,texture.getSize().y/framesize.y);
		m_wrap_rows = true;
		break;
	default:
		break;
	}
}
void AnimatedSprite::setTexture(const sf::Texture& texture)
{
	m_textureRect = sf::IntRect(0,0,m_framesize.x,m_framesize.y);
    m_texture = &texture;
}
void AnimatedSprite::setColor(const sf::Color& color)
{
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}

const sf::Texture* AnimatedSprite::getTexture() const
{
    return m_texture;
}
const sf::Color& AnimatedSprite::getColor() const
{
    return m_vertices[0].color;
}
sf::FloatRect AnimatedSprite::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(m_textureRect.width));
    float height = static_cast<float>(std::abs(m_textureRect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}
sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}
void AnimatedSprite::setFrame(int pos)
{
	m_frameposition.x = pos;
}
void AnimatedSprite::setRow(int pos)
{
	m_frameposition.y = pos;
}
void AnimatedSprite::setFrameDuration(sf::Time duration)
{
	m_frameduration = duration;
}

sf::Time AnimatedSprite::getFrameDuration() const
{
	return m_frameduration;
}
int AnimatedSprite::getFrame() const
{
	return m_frameposition.x;
}
int AnimatedSprite::getRow() const
{
	return m_frameposition.y;
}

void AnimatedSprite::update()
{
	
	if(m_updatetimer.getElapsedTime() > m_frameduration)
	{
		m_frameposition.x++;
		if(m_wrap_rows)
		{
			if(m_frameposition.x >= m_frames.x)
			{
				m_framesize.y++;
				if(m_frameposition.y >= m_frames.y)
				{
					m_frameposition = sf::Vector2i(0,0);
				}
			}
		}
		else
		{
			if(m_frameposition.x >= m_frames.x)
			{
				
				m_frameposition.x = 0;
			}
		}
		sf::Vector2i pos(m_frameposition.x*m_framesize.x,m_frameposition.y*m_framesize.y);
		m_textureRect = sf::IntRect(pos, m_framesize);
		updatePositions();
		updateTexCoords();
		m_updatetimer.restart();
	}
}

////////////////////////
void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_texture)
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::Quads, states);
    }
}

void AnimatedSprite::updatePositions()
{
    sf::FloatRect bounds = getLocalBounds();

    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(0, bounds.height);
    m_vertices[2].position = sf::Vector2f(bounds.width, bounds.height);
    m_vertices[3].position = sf::Vector2f(bounds.width, 0);
}
void AnimatedSprite::updateTexCoords()
{
    float left   = static_cast<float>(m_textureRect.left);
    float right  = left + m_textureRect.width;
    float top    = static_cast<float>(m_textureRect.top);
    float bottom = top + m_textureRect.height;

    m_vertices[0].texCoords = sf::Vector2f(left, top);
    m_vertices[1].texCoords = sf::Vector2f(left, bottom);
    m_vertices[2].texCoords = sf::Vector2f(right, bottom);
    m_vertices[3].texCoords = sf::Vector2f(right, top);
}