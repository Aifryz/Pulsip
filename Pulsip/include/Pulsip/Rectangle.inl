template<class T>
Rectangle<T>::Rectangle() :
	m_position(0, 0),
	m_halfsize(0, 0)
{}
template<class T>
Rectangle<T>::Rectangle(const sf::Vector2<T>& position, const sf::Vector2<T>& size) :
	m_halfsize(sf::Vector2<T>(std::abs(size.x), std::abs(size.y)) / static_cast<T>(2)),
	m_position(position)
{}
template<class T>
Rectangle<T>::Rectangle(T left, T right, T top, T bottom) :
	m_halfsize(sf::Vector2<T>(std::abs(right - left) / static_cast<T>(2), std::abs(bottom - top) / static_cast<T>(2))),
	m_position(sf::Vector2<T>((right + left) / static_cast<T>(2), (bottom + top) / static_cast<T>(2)))
{}
template<class T>
template<class U>
Rectangle<T>::Rectangle(const Rectangle<U>& other) :
	m_halfsize(static_cast<sf::Vector2<T>>(other.getSize() / static_cast<U>(2))),
	m_position(static_cast<sf::Vector2<T>>(other.getPosition()))
{}
template<class T>
void Rectangle<T>::setSize(const sf::Vector2<T>& size)
{
	m_halfsize = sf::Vector2<T>(std::abs(size.x), std::abs(size.y)) / static_cast<T>(2);
}
template<class T>
void Rectangle<T>::setPosition(const sf::Vector2<T>& position)
{
	m_position = position;
}
template<class T>
const sf::Vector2<T>& Rectangle<T>::getSize() const
{
	return m_halfsize*static_cast<T>(2);
}
template<class T>
const sf::Vector2<T>& Rectangle<T>::getHalfSize() const
{
	return m_halfsize;
}
template<class T>
const sf::Vector2<T>& Rectangle<T>::getPosition() const
{
	return m_position;
}
template<class T>
T Rectangle<T>::left() const
{
	return m_position.x - m_halfsize.x;
}
template<class T>
T Rectangle<T>::right() const
{
	return m_position.x + m_halfsize.x;
}
template<class T>
T Rectangle<T>::top() const
{
	return m_position.y - m_halfsize.y;
}
template<class T>
T Rectangle<T>::bottom() const
{
	return m_position.y + m_halfsize.y;
}
template<class T>
bool Rectangle<T>::intersects(const Rectangle<T>& rect) const
{
	sf::Vector2<T> distance = rect.getPosition() - m_position;
	sf::Vector2<T> mindistanec = rect.getHalfSize() + m_halfsize;
	sf::Vector2<T> absdst = sf::Vector2<T>(std::abs(distance.x), std::abs(distance.y));
	sf::Vector2<T> difference = (m_halfsize + rect.getHalfSize()) - absdst;
	if (difference.x > 0 && difference.y > 0)//we check if there's collision on both axis
		return true;
	return false;
}
template<class T>
bool Rectangle<T>::contains(const Rectangle<T>& rect) const
{
	if (rect.left() > left() &&
		rect.right() < right() &&
		rect.top() > top() &&
		rect.bottom() < bottom())
		return true;
	return false;
}
template<class T>
bool Rectangle<T>::contains(T x, T y) const
{
	if (left() < x && right() > x && top() < y && bottom() > y)
		return true;
	return false;
}
template<class T>
bool Rectangle<T>::contains(const sf::Vector2<T>& point) const
{
	return contains(point.x, point.y);
}
//TODO:Move this method to entity class or something else
//template<class T>
//bool Rectangle<T>::ejectFrom(const Rectangle<T>& rect)
//{
//	sf::Vector2<T> distance = rect.getPosition() - m_position;
//	sf::Vector2<T> mindistance = rect.getHalfSize() + m_halfsize;
//	sf::Vector2<T> absdst = sf::Vector2<T>(std::abs(distance.x), std::abs(distance.y));
//	sf::Vector2<T> difference = mindistance - absdst;
//	if (difference.x > 0 && difference.y > 0)//we check if there's collision on both axis
//	{
//		if (difference.x < difference.y)//eject in the axis where there's smallest difference
//		{
//			m_position += sf::Vector2<T>(sign.x*difference.x, 0);
//		}
//		else
//		{
//			m_position += sf::Vector2<T>(0, sign.y*difference.y);
//		}
//		return true;
//	}
//	return false;
//}
template<class T>
bool Rectangle<T>::operator ==(const Rectangle<T>& other)
{
	if (m_position == other.m_position && m_halfsize == other.m_halfsize)
		return true;
	return false;
}
template<class T>
bool Rectangle<T>::operator !=(const Rectangle<T>& other)
{
	if (m_position != other.m_position && m_halfsize != other.m_halfsize)
		return true;
	return false;
}
