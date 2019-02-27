// Source file for the Pyramid.hpp header

#include "Pyramid.hpp"

std::vector<sf::Vector3f> pyramid()
{
    std::vector<sf::Vector3f> ret;
    
    ret.push_back(sf::Vector3f(0,0,0));
    ret.push_back(sf::Vector3f(6,0,0));

    ret.push_back(sf::Vector3f(6,0,0));
    ret.push_back(sf::Vector3f(6,6,0));

    ret.push_back(sf::Vector3f(6,6,0));
    ret.push_back(sf::Vector3f(0,6,0));

    ret.push_back(sf::Vector3f(0,6,0));
    ret.push_back(sf::Vector3f(0,0,0));

    ret.push_back(sf::Vector3f(0,0,0));
    ret.push_back(sf::Vector3f(3,3,9));

    ret.push_back(sf::Vector3f(0,6,0));
    ret.push_back(sf::Vector3f(3,3,9));

    ret.push_back(sf::Vector3f(6,6,0));
    ret.push_back(sf::Vector3f(3,3,9));

    ret.push_back(sf::Vector3f(6,0,0));
    ret.push_back(sf::Vector3f(3,3,9));

    return ret;
}



sf::VertexArray projectEndpoints(const std::vector<sf::Vector3f>& object, const Projector& projector)
{
    sf::VertexArray ret(sf::Lines, object.size());

    // iterate through the array and set the positions to the projected points
    for(std::vector<sf::Vector3f>::size_type i = 0; i != object.size(); ++i)
        ret[i].position = projector.project(object[i]);
    
    // return the vertex array
    return ret;
}