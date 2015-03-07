#ifndef PULSIP_UTIL_HPP
#define PULSIP_UTIL_HPP
#include<vector>
#include<iostream>
#include"SFML/System/Vector2.hpp"
namespace pul
{
	///Erases element at [index], replaces it with last element of vector
	///Does not check if index is outside of vector's range
	template<class T>
	void fastErase(std::vector<T>& vector,size_t index)
	{
		std::swap(vector[index], vector.back());
		vector.pop_back();
	}
    ///Creates index form given position and size
    ///Used to map 2d elements to 1d array
    template<class T>
    T indexify(sf::Vector2<T> position, sf::Vector2<T> size)
    {
        return position.y*size.x + position.x;
    }
    ///Creates position form given index and size
    ///Used to reverse the idexify position
    template<class T>
    sf::Vector2<T> deindexify(T index, sf::Vector2<T> size)
    {
        T x = index % size.x;
        T y = index / size.x;
        return sf::Vector2<T>(x, y);
    }
    ///Component-wise clip of vector to desired lenght
    ///Prerequisites: min.x <= max.x and min.y <= max.y
    template<class T>
    sf::Vector2<T> clip(sf::Vector2<T> vec, sf::Vector2<T> min, sf::Vector2<T> max)
    {
        if (vec.x < min.x)
            vec.x = min.x;
        if (vec.y < min.y)
            vec.y = min.y;

        if (vec.x > max.x)
            vec.x = max.x;
        if (vec.y > max.y)
            vec.y = max.y;
        return vec;
    }
    
}
#endif // !PULSIP_UTIL_HPP
