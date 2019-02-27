#ifndef GUARD__VECTOR_OPERATIONS_H
#define GUARD__VECTOR_OPERATIONS_H

#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include <cmath>


/*
**************************************************
DOT PRODUCT
**************************************************
*/

template<class T>
float dot(sf::Vector2<T> vec1, sf::Vector2<T> vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}


template<class T>
float dot(sf::Vector3<T> vec1, sf::Vector3<T> vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}


/*
**************************************************
CROSS PRODUCT
**************************************************
*/

template<class T>
sf::Vector3f cross(sf::Vector3<T> vec1, sf::Vector3<T> vec2)
{
    return sf::Vector3f(
        vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x
        );
}


/*
**************************************************
MAGNITUTE
**************************************************
*/

template<class T>
float magnitude(sf::Vector3<T> vec)
{
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2)+std::pow(vec.z, 2));
}


template<class T>
float magnitude(sf::Vector2<T> vec)
{
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
}

/*
**************************************************
UNIT VECTORS
**************************************************
*/

// template function to return a 2D vector length one, in the same direction as the given vector
template<class T>
sf::Vector2<float> unitVector(sf::Vector2<T> vec)
{
    // obtain the magnitude of the vector
    float magnitude = std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));

    // check for zero vector
    if(magnitude == 0)
    {
        sf::Vector2f ret(0, 0);
        return ret;
    }

    // if non-zero, return the scaled vector
    sf::Vector2<float> ret(vec.x / magnitude, vec.y / magnitude);
    return ret;

}

// template function to return a 3D vector length one, in the same direction as the given vector
template<class T>
sf::Vector3<float> unitVector(sf::Vector3<T> vec)
{
    // obtain the magnitude of the vector
    float magnitude = std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2) + std::pow(vec.z, 2));

    // check for zero vector
    if(magnitude == 0)
    {
        sf::Vector3f ret(0, 0, 0);
        return ret;
    }

    // if non-zero, return the scaled vector
    sf::Vector3<float> ret(vec.x / magnitude, vec.y / magnitude, vec.z / magnitude);
    return ret;

}

// template function returns the 2D unit vector in direction pos1 -> pos2
template<class T>
sf::Vector2<float> unitVector(sf::Vector2<T> pos1, sf::Vector2<T> pos2)
{
    // first obtain the vector joining the two positions
    sf::Vector2<T> vec(pos2.x - pos1.x, pos2.y - pos1.y);

    // now use previous template to return apropriate unit vector
    return unitVector(vec);
}


// template function returns the 3D unit vector in direction pos1 -> pos2
template<class T>
sf::Vector3<float> unitVector(sf::Vector3<T> pos1, sf::Vector3<T> pos2)
{
    // first obtain the vector joining the two positions
    sf::Vector3<T> vec(pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z);

    // now use previous template to return apropriate unit vector
    return unitVector(vec);
}

/*
**************************************************
ANGLE
**************************************************
*/

// returns angle to the positive x-axis in range [0, 360]
template<class T>
float angle(sf::Vector2<T> vec)
{
    float princ_angle =  std::atan(vec.y / vec.x) * 180 / 3.141;

    // calculate case
    if((vec.x > 0 && vec.y > 0) || (vec.x > 0 && vec.y < 0))
    {
        return princ_angle;
    } else {
        return princ_angle + 180;
    }
}


#endif