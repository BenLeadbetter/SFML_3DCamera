#ifndef GUARD__PROJECTOR_HPP
#define GUARD__PROJECTOR_HPP
// this Projector class will project 3D vectors to our new 2D coordinate system

#include "SFML/System/Vector3.hpp"
#include "SFML/System/Vector2.hpp"
#include "Matrix.hpp"

class Projector
{
    friend class Camera;
    
    public:
        Projector() {};
        Projector(const sf::Vector3f&, const sf::Vector3f&, const float&);
        ~Projector() {};

        sf::Vector2f project(const sf::Vector3f&) const;

        void setCameraPos(const sf::Vector3f&);
        void setCameraPos(const sf::Vector3f&, const sf::Vector3f&);
        void setCameraDir(const sf::Vector3f&);
        void setCameraDir(const sf::Vector3f&, const sf::Vector3f&);
        void setZoom(const float&);
        void setZoom(const float&, const sf::Vector3f&);


    private:

        sf::Vector3f bringToProjectionPlane(const sf::Vector3f&) const;
        void generateMatrix();
        void generateMatrix(sf::Vector3f);

        sf::Vector3f m_CameraPosition;
        sf::Vector3f m_CameraDirection;
        float m_CameraZoom;
        Matrix m_BasisChange;
};

#endif