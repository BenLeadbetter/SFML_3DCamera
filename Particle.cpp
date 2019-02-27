// source file for the Particle class

#include "Particle.hpp"
#include "vector_operations.hpp"
#include <cmath>
#include <algorithm>

Particle::Particle()
{
    // initiate the member variables
    m_Position = sf::Vector3f(0, 0, 0);
    m_Velocity = sf::Vector3f(0, 0, 0);
    m_NetForce = sf::Vector3f(0, 0, 0);
    m_Mass = 1.0f;

    // Initiate the circle shape for drawing
    m_Circle.setRadius(1.0);
    m_Circle.setOrigin(sf::Vector2f(0.5f, 0.5f));
    m_Circle.setFillColor(sf::Color::Green);
}

Particle::Particle(const sf::Vector3f& position, const sf::Vector3f& velocity, const float& mass)
{
    // initiate the member variables
    m_Position = position;
    m_Velocity = velocity;
    m_NetForce = sf::Vector3f(0, 0, 0);
    m_Mass = mass;

    // Initiate the circle shape for drawing
    m_Circle.setFillColor(sf::Color::Green);
}

void Particle::setPosition(const sf::Vector3f& position)
{
    m_Position = position;
}

void Particle::setVelocity(const sf::Vector3f& velocity)
{
    m_Velocity = velocity;
}

void Particle::setMass(const float& mass)
{
    m_Mass = mass;
}

void Particle::setColour(sf::Color colour)
{
    m_Circle.setFillColor(colour);
}

sf::Vector3f Particle::getPosition() const
{
    return m_Position;
}

sf::Vector3f Particle::getVelocity() const
{
    return m_Velocity;
}

sf::Vector3f Particle::getForce() const
{
    return m_NetForce;
}

float Particle::getMass() const
{
    return m_Mass;
}

void Particle::addForce(const sf::Vector3f& force)
{
    m_NetForce += force;
}

void Particle::clearForce()
{
    m_NetForce = sf::Vector3f(0, 0, 0);
}

void Particle::update(sf::Time dt)
{
    // update the position based on current velocity
    m_Position += m_Velocity * dt.asSeconds();

    // update the velocity dep on mass and force
    m_Velocity += m_NetForce * dt.asSeconds() / m_Mass;
}

void Particle::draw(sf::RenderWindow& window, const Camera& camera)
{
    m_Circle.setRadius(std::pow(m_Mass, 0.3333) * camera.getZoom() / camera.distanceFromCamera(m_Position));
    m_Circle.setOrigin(sf::Vector2f(m_Circle.getLocalBounds().width / 2, m_Circle.getLocalBounds().width / 2));
    sf::Vector2f projectedPos = camera.capture(m_Position);
    m_Circle.setPosition(projectedPos);

    // draw to the window
    window.draw(m_Circle);
}

// functions to sort a vector of particles
bool depthCompare(const Particle& particle1, const Particle& particle2, const Camera& camera)
{
    return camera.distanceFromCamera(particle1.getPosition()) < camera.distanceFromCamera(particle2.getPosition());
}

void sort(std::vector<Particle>& vec, const Camera& camera)
{
    bool checking = true;
    while(checking)
    {
        checking = false;
        // iterate through the vector
        for(std::vector<Particle>::iterator iter = vec.begin(); iter != vec.end() - 1; ++iter)
        {
            // compare each pair of elements
            if(depthCompare(*iter, *(iter + 1), camera))
            {
                // swap the two items
                std::iter_swap(iter, iter + 1);
                checking = true;
            }

        }
    }
}

void drawParticles(std::vector<Particle>& vec, sf::RenderWindow& window, const Camera& camera)
{
    // first, sort the vector
    sort(vec, camera);

    // then iterate through the vector drawing each particle
    for(auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        iter->draw(window, camera);
    }
}

void applyGravity(std::vector<Particle>& vec)
{
    // define gravitational constant
    static float G = 50.0;

    // apply force to each particle in the vector
    for(std::vector<Particle>::size_type i = 0; i != vec.size(); i++)
    {
        // clear any previous forces
        vec[i].clearForce();

        // apply a force from each other particle
        for(std::vector<Particle>::size_type j = 0; j != vec.size(); ++j)
        {
            // only apply gravitational forces from other particles
            if(j != i)
            {
                // grab the deisplacement vector to the other particle
                sf::Vector3f disp = vec[j].getPosition() - vec[i].getPosition();

                // direct the force towards the other particle
                sf::Vector3f force = unitVector(disp);

                // grab the reciprocal square of the distance
                float invSq = 1.0f / std::pow(magnitude(disp), 2);

                // scale force according to the masses and distance and G
                force = force * G * vec[i].getMass() * vec[j].getMass() * invSq;

                // add it to the particle's net force
                vec[i].addForce(force);
            }
        }
    }
}