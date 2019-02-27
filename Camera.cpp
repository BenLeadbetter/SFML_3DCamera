// Source file for the Camera.hpp header

#include "Camera.hpp"
#include "vector_operations.hpp"
#include <cmath>

// constructor
Camera::Camera():
m_ANGLESPEED(0.9),
m_LINEARSPEED(30),
m_INIT_ALPHA(0.0f),
m_INIT_BETA(0.0f),
m_RADIUS(50),
m_INIT_ZOOM(1500),
m_Projector(),
m_alpha(m_INIT_ALPHA),
m_beta(m_INIT_BETA),
m_zoom(m_INIT_ZOOM),
m_LeftPressed(false),
m_RightPressed(false),
m_Uppressed(false),
m_DownPressed(false),
m_W_Pressed(false),
m_A_Pressed(false),
m_S_Pressed(false),
m_D_pressed(false)
{
    m_InitFocalPoint = sf::Vector3f(0, 0, 0);
    m_FocalPoint = m_InitFocalPoint;
    m_Displacement = sf::Vector3f(0, 0, 0);
    m_CameraPos = sf::Vector3f(m_RADIUS * std::cos(m_INIT_ALPHA), m_RADIUS * std::sin(m_INIT_ALPHA), 0);
    m_CameraDir = m_FocalPoint - m_CameraPos;
    m_Projector.setCameraPos(m_CameraPos);
    m_Projector.setCameraDir(m_CameraDir);
    m_Projector.setZoom(m_INIT_ZOOM);
}

// setters
// possibly too many calls to reevaluate the matrix(??) - we shall see
void Camera::setPosition(const sf::Vector3f& cameraPos)
{
    m_Projector.setCameraPos(cameraPos);
    m_Projector.setCameraDir(m_InitFocalPoint + m_Displacement - cameraPos);
}

void Camera::setZoom(float zoom)
{
    m_Projector.setZoom(zoom, m_Displacement);
}

void Camera::setFocalPoint(const sf::Vector3f& pos)
{
    m_InitFocalPoint = pos;
    setPosition(m_CameraPos);
}

// getters
sf::Vector3f Camera::getPosition() const
{
    return m_CameraPos;
}

sf::Vector3f Camera::getDirection() const
{
    return m_CameraDir;
}

float Camera::getZoom() const
{
    return m_zoom;
}

// control movement
void Camera::rotateLeft()
{
    m_LeftPressed = true;
}

void Camera::rotateRight()
{
    m_RightPressed = true;
}

void Camera::rotateUp()
{
    m_Uppressed = true;
}

void Camera::rotateDown()
{
    m_DownPressed = true;
}

void Camera::stopRotateLeft()
{
    m_LeftPressed = false;
}

void Camera::stopRotateRight()
{
    m_RightPressed = false;
}

void Camera::stopRotateUp()
{
    m_Uppressed = false;
}

void Camera::stopRotateDown()
{
    m_DownPressed = false;
}

void Camera::moveLeft()
{
    m_A_Pressed = true;
}

void Camera::moveRight()
{
    m_D_pressed = true;
}

void Camera::moveForward()
{
    m_W_Pressed = true;
}

void Camera::moveBack()
{
    m_S_Pressed = true;
}

void Camera::stopLeft()
{
    m_A_Pressed = false;
}

void Camera::stopRight()
{
    m_D_pressed = false;
}

void Camera::stopForward()
{
    m_W_Pressed = false;
}

void Camera::stopBack()
{
    m_S_Pressed = false;
}

void Camera::zoom(const float& delta)
{
    
    m_zoom += 50 * delta;
    if(m_zoom < 0) m_zoom = 0;
    m_Projector.setZoom(m_zoom, m_Displacement);
}

// update function
void Camera::update(sf::Time dt)
{
    bool cameraFiddled = false;

    // reset the angles and vectors according to movement commands
    if( 
        m_LeftPressed || m_RightPressed || m_DownPressed || m_Uppressed ||
        m_W_Pressed || m_A_Pressed || m_S_Pressed || m_D_pressed
        )
    {
        m_alpha += m_ANGLESPEED * (m_LeftPressed - m_RightPressed) * dt.asSeconds();
        m_beta += m_ANGLESPEED * (m_Uppressed - m_DownPressed) * dt.asSeconds();

        // establish directions for forward and right
        sf::Vector3f forward = unitVector(sf::Vector3f(m_CameraDir.x, m_CameraDir.y, 0));
        sf::Vector3f right =  cross(sf::Vector3f(0, 0, 1), forward);

        // update the displacement vector
        m_Displacement += (m_LINEARSPEED * dt.asSeconds() * (m_W_Pressed - m_S_Pressed)) * forward;
        m_Displacement += (m_LINEARSPEED * dt.asSeconds() * (m_D_pressed - m_A_Pressed)) * right;

        // restrict the angles
        if(m_beta < - 1.5706) m_beta = -1.5706;
        if(m_beta > 1.5707) m_beta = 1.5707;
        if(m_alpha > 6.283) m_alpha -= 6.283;
        if(m_alpha < 0) m_alpha += 6.283;

        cameraFiddled = true;
    }

    // reset camera position if any movement occured
    if(cameraFiddled)
    {
        m_CameraPos = sf::Vector3f(
                                    m_RADIUS * std::cos(m_alpha) * std::cos(m_beta), 
                                    m_RADIUS * std::sin(m_alpha) * std::cos(m_beta), 
                                    m_RADIUS * std::sin(m_beta)
                                ) + m_Displacement;
        m_FocalPoint = m_InitFocalPoint + m_Displacement;
        m_CameraDir = m_FocalPoint - m_CameraPos;
        m_Projector.setCameraPos(m_CameraPos, m_Displacement);
        m_Projector.setCameraDir(m_CameraDir, m_Displacement); 
    }

}

// capture
sf::VertexArray Camera::captureLines(const std::vector<sf::Vector3f>& object) const
{
    sf::VertexArray ret(sf::Lines, object.size());

    // iterate through the array and set the positions to the projected points
    for(std::vector<sf::Vector3f>::size_type i = 0; i != object.size(); ++i)
        ret[i].position = m_Projector.project(object[i]);
    
    // return the vertex array
    return ret;
}

sf::Vector2f Camera::capture(const sf::Vector3f& vec) const
{
    return m_Projector.project(vec);
}

float Camera::distanceFromCamera(const sf::Vector3f& pos) const
{
    return magnitude(pos - m_CameraPos);
}