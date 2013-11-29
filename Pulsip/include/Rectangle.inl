template<typename T>
Rectangle<T>::Rectangle():
		m_position(0,0),
		m_halfsize(0,0)
	{}
template<typename T>
	Rectangle<T>::Rectangle(sf::Vector2<T>& size, sf::Vector2<T>& position):
		m_halfsize(size/2),
		m_position(position)
	{}
	template<typename T>
	Rectangle<T>::Rectangle(T left, T right, T top, T bottom):
		m_halfsize(sf::Vector2<T>((right-left)/2,(bottom-top)/2)),
		m_position(sf::Vector2<T>((right+left)/2,(bottom+top)/2))
	{}
	template<typename T>
	template<typename U>
    Rectangle<T>::Rectangle(const Rectangle<U>& other):
		m_halfsize(static_cast<sf::Vector2<T>>( other.getSize()/2 )),
		m_position(static_cast<sf::Vector2<T>>( other.getPosition() ))
	{}
		template<typename T>
	void Rectangle<T>::setSize(sf::Vector2<T> size)
	{ 
		m_halfsize = size/2;
	}
	template<typename T>
	void Rectangle<T>::setPosition(sf::Vector2<T> position)
	{
		m_position = position;
	}
	template<typename T>
	sf::Vector2<T> Rectangle<T>::getSize() const
	{
		return m_halfsize*2;
	}
	template<typename T>
	sf::Vector2<T> Rectangle<T>::getPosition() const
	{
		return m_position;
	}
	template<typename T>
	bool Rectangle<T>::intersects(const Rectangle<T>& rect) const
	{
		return false;
	}
	template<typename T>
	bool Rectangle<T>::contains(const Rectangle<T>& rect) const
	{
		return false;
	}
	template<typename T>
	bool Rectangle<T>::contains(T x, T y)
	{
		return false;
	}
	template<typename T>
	bool Rectangle<T>::contains(const sf::Vector2<T>& point)
	{
		return false;
	}
	template<typename T>
	bool Rectangle<T>::ejectFrom(const Rectangle<T>& rect)
	{
		return false;
	}
	template<typename T>

	bool Rectangle<T>::operator ==(const Rectangle<T>& other)
	{
		if(m_position == other.m_position && m_halfsize == other.m_halfsize)
			return true;
		return false;
	}
	template<typename T>
	bool Rectangle<T>::operator !=(const Rectangle<T>& other)
	{
		if(m_position != other.m_position && m_halfsize != other.m_halfsize)
			return true;
		return false;
	}