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
}
#endif // !PULSIP_UTIL_HPP
