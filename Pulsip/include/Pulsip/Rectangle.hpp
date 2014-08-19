#ifndef PULSIP_RECTANGLE_HPP
#define PULSIP_RECTANGLE_HPP
#include<SFML/System.hpp>
namespace pul
{
	///Utility class representing 2D, axix aligned rectangle
	///T has to be either floating point or integer since internal code uses std::abs() in some places 
	template<class T>
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(const sf::Vector2<T>& position, const sf::Vector2<T>& size);
		Rectangle(T left, T right, T top, T bottom);
		template <class U>
		explicit Rectangle(const Rectangle<U>& other);
		void setSize(const sf::Vector2<T>& size);
		void setPosition(const sf::Vector2<T>& position);
		const sf::Vector2<T>& getSize() const;
		const sf::Vector2<T>& getHalfSize() const;
		const sf::Vector2<T>& getPosition() const;
		T left() const;
		T right() const;
		T top() const;
		T bottom() const;
		bool intersects(const Rectangle<T>& rect) const;
		bool contains(const Rectangle<T>& rect) const;
		bool contains(T x, T y) const;
		bool contains(const sf::Vector2<T>& point) const;

		bool operator ==(const Rectangle<T>& other);
		bool operator !=(const Rectangle<T>& other);
	private:
		sf::Vector2<T> m_position;
		sf::Vector2<T> m_halfsize;


	};
	//Include implementation
	#include<Pulsip/Rectangle.inl>
	///Typedef for mostly used template
	typedef Rectangle<float> AABB;
}

#endif // !RECTANGLE_HPP
