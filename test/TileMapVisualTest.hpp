#include"gtest\gtest.h"
#include<Pulsip/TileMap.hpp>
#include<vector>
class TileMapVisualTest : public testing::Test
{
public:
	TileMapVisualTest() :
		txt(),
		tm(txt, sf::Vector2u(10U, 10U), sf::Vector2f(32.f, 32.f), 1)
	{
		m_window.create(sf::VideoMode(800U, 600U), "Testing");
		txt.loadFromFile("map.png");
		txt.setSmooth(true);
	}
	virtual void SetUp()
	{
		for (size_t x = 0; x < 10; x++)
		{
			for (size_t y = 0; y < 10; y++)
			{
				tm.getFaceAtIndex(x, y, 0)->setTextureRectangle(sf::FloatRect(0.f, 0.f, 32.f, 32.f));
			}
		}
	}
	virtual void TearDown()
	{

	}
	sf::RenderWindow m_window;
	pul::TileMap tm;
	sf::Texture txt;
};
TEST_F(TileMapVisualTest, General)
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Q:
					tm.setScale(0.5f, 0.5f);
					tm.setOrigin(160.f, 160.f);
					tm.rotate(50.f);
					tm.setPosition(50.f, 50.f);
					break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				tm.getFace(pos)->setColor(sf::Color::Red);
			}
		}
		m_window.clear();
		m_window.draw(tm);
		m_window.display();
	}
	std::vector<int> vec;
}