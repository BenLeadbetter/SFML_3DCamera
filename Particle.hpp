#ifndef GUARD__PARTICLE_HPP
#define GUARD__PARTICLE_HPP
// header file for the Partcile class

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Camera.hpp"

class Particle
{
    public:
        Particle();
        Particle(const sf::Vector3f&, const sf::Vector3f&, const float&);
        ~Particle() {};

        // setters
        void setPosition(const sf::Vector3f&);
        void setVelocity(const sf::Vector3f&);
        void setMass(const float&);
        void setColour(sf::Color);

        // getters
        sf::Vector3f getPosition() const;
        sf::Vector3f getVelocity() const;
        sf::Vector3f getForce() const;
        float getMass() const;

        // physics
        void addForce(const sf::Vector3f&);
        void clearForce();
        void update(sf::Time dt);

        // render
        void draw(sf::RenderWindow&, const Camera&);

    private:
        sf::Vector3f        m_Position;
        sf::Vector3f        m_Velocity;
        sf::Vector3f        m_NetForce;
        float               m_Mass;
        sf::CircleShape     m_Circle;
};

// function to compare vector of particles based on depth
bool depthCompare(const Particle&, const Particle&, const Camera&);

// function to sort a vector of particles in order of depth
void sort(std::vector<Particle>&, const Camera&);

// function to draw a vector of particles in the correct order
void drawParticles(std::vector<Particle>&, sf::RenderWindow&, const Camera&);

// function to apply interaction-gravitational force between a system of particles
void applyGravity(std::vector<Particle>&);


#endif