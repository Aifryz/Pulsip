#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"SFML/Graphics.hpp"

///Utility class for manipulating 2D, centered, axis aligned rectangles
template<typename T> 
class Rectangle
{
public:
	Rectangle();
	Rectangle(sf::Vector2<T>& size, sf::Vector2<T>& position);
	Rectangle(T left, T right, T top, T bottom);
	template <typename U>
    explicit Rectangle(const Rectangle<U>& other);

	void setSize(sf::Vector2<T> size);
	void setPosition(sf::Vector2<T> position);
	sf::Vector2<T> getSize() const;
	sf::Vector2<T> getPosition() const;
	
	bool intersects(const Rectangle<T>& rect) const;
	bool contains(const Rectangle<T>& rect) const;
	bool contains(T x, T y);
	bool contains(const sf::Vector2<T>& point);
	bool ejectFrom(const Rectangle<T>& rect);
	
	bool operator ==(const Rectangle<T>& other);
	bool operator !=(const Rectangle<T>& other);
	
private:
	sf::Vector2<T> m_position;
	sf::Vector2<T> m_halfsize;


};
#include"Rectangle.inl"
typedef Rectangle<float> FloatRectangle;

#endif // !RECTANGLE_H
