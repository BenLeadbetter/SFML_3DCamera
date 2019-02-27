#ifndef GUARD__CAMERA_HPP
#define GUARD__CAMERA_HPP
// header file for the Camera class

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include "Projector.hpp"

class Camera
{
    public:

        // constructor and destructor
        Camera();
        ~Camera() {};
        
        // setters
        void setPosition(const sf::Vector3f&);
        void setZoom(float);
        void setFocalPoint(const sf::Vector3f&);

        // getters
        sf::Vector3f getPosition() const;
        sf::Vector3f getDirection() const;
        float getZoom() const;

        // contol movement
        void rotateLeft();
        void rotateRight();
        void rotateUp();
        void rotateDown();
        void stopRotateLeft();
        void stopRotateRight();
        void stopRotateUp();
        void stopRotateDown();
        void moveLeft();
        void moveRight();
        void moveForward();
        void moveBack();
        void stopLeft();
        void stopRight();
        void stopForward();
        void stopBack();
        void zoom(const float&);

        // update
        void update(sf::Time);

        // capture a 3D entity
        sf::VertexArray captureLines(const std::vector<sf::Vector3f>&) const;
        sf::Vector2f capture(const sf::Vector3f&) const;
        float distanceFromCamera(const sf::Vector3f&) const;

    
    private:

        // constants
        const float m_ANGLESPEED;
        const float m_LINEARSPEED;
        const float m_INIT_ALPHA;
        const float m_INIT_BETA;
        const float m_RADIUS;
        const float m_INIT_ZOOM;

        // the projector
        Projector m_Projector;

        // variables for camera control
        float m_alpha;
        float m_beta;
        float m_zoom;
        sf::Vector3f m_FocalPoint;
        sf::Vector3f m_InitFocalPoint;
        sf::Vector3f m_Displacement;
        sf::Vector3f m_CameraPos;
        sf::Vector3f m_CameraDir;

        // booleans for camera movement
        bool m_LeftPressed;
        bool m_RightPressed;
        bool m_Uppressed;
        bool m_DownPressed;
        bool m_W_Pressed;
        bool m_A_Pressed;
        bool m_S_Pressed;
        bool m_D_pressed;

};


#endif