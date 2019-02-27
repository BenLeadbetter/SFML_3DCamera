#ifndef GUARD__PYRAMID_HPP
#define GUARD__PYRAMID_HPP

#include "SFML/System/Vector3.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "Projector.hpp"
#include <vector>

// returns the end points for the eight lines making up a square-based pyramid
std::vector<sf::Vector3f> pyramid();

// projects end points of lines to a vertex array
sf::VertexArray projectEndpoints(const std::vector<sf::Vector3f>&, const Projector&);


#endif