#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "Particle.hpp"
#include "Pyramid.hpp"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1000, 800), "3D Orbits", Style::Default);
    window.setFramerateLimit(100);
    
    // create the 3D particles
    Particle particle1;
    particle1.setMass(15.0);
    particle1.setPosition(sf::Vector3f(0, 10, 0));
    particle1.setVelocity(sf::Vector3f(0, 0, 0));

    Particle particle2;
    particle2.setMass(3);
    particle2.setPosition(sf::Vector3f(0, -10, 0));
    particle2.setVelocity(sf::Vector3f(3, 0, 2));
    particle2.setColour(sf::Color::Blue);

    Particle particle3;
    particle3.setMass(5.0);
    particle3.setPosition(sf::Vector3f(3, 0, 0));
    particle3.setVelocity(sf::Vector3f(2, -5, -1));
    particle3.setColour(sf::Color::Red);

    std::vector<Particle> particleVec;
    particleVec.push_back(particle1);
    particleVec.push_back(particle2);
    particleVec.push_back(particle3);
    


    // A camera to veiw the object
    Camera camera;
    camera.setFocalPoint(sf::Vector3f(3, 3, 4));

    
    // create a pyramid object
    //std::vector<sf::Vector3f> pyramidObject = pyramid();
    

    // Time control
    Clock clock;
    Time dt;


    // start main loop
    while(window.isOpen())
    {
        /*
        ***************************************
        HANDLE INPUT
        ***************************************
        */
        // poll events
        Event event;
        while(window.pollEvent(event))
        {
            // handle quitting
            if(event.type == sf::Event::EventType::Closed)
            {
                window.close();
            }

            // handle camera movements
            if(event.type == sf::Event::EventType::KeyPressed)
            {
                if(event.key.code == Keyboard::Left)
                    camera.rotateLeft();
                
                if(event.key.code == Keyboard::Right)
                    camera.rotateRight();
                
                if(event.key.code == Keyboard::Up)
                    camera.rotateUp();
                
                if(event.key.code == Keyboard::Down)
                    camera.rotateDown();

                if(event.key.code == Keyboard::A)
                    camera.moveLeft();
                
                if(event.key.code == Keyboard::D)
                    camera.moveRight();
                
                if(event.key.code == Keyboard::W)
                    camera.moveForward();
                
                if(event.key.code == Keyboard::S)
                    camera.moveBack();
            }

            if(event.type == sf::Event::EventType::KeyReleased)
            {
                if(event.key.code == Keyboard::Left)
                    camera.stopRotateLeft();
                
                if(event.key.code == Keyboard::Right)
                    camera.stopRotateRight();
                
                if(event.key.code == Keyboard::Up)
                    camera.stopRotateUp();
                
                if(event.key.code == Keyboard::Down)
                    camera.stopRotateDown();

                if(event.key.code == Keyboard::A)
                    camera.stopLeft();
                
                if(event.key.code == Keyboard::D)
                    camera.stopRight();
                
                if(event.key.code == Keyboard::W)
                    camera.stopForward();
                
                if(event.key.code == Keyboard::S)
                    camera.stopBack();
            }

            if(event.type == sf::Event::EventType::MouseWheelMoved)
            {
                camera.zoom(event.mouseWheel.delta);
            }

        } // end event polling
        
        /*
        ***************************************
        UPDATE THE FRAME
        ***************************************
        */

        // update the frame
        dt = clock.restart();

        // update the camera
        camera.update(dt);

        // apply gravitational forces to particles
        applyGravity(particleVec);

        // update the particles
        for(std::vector<Particle>::iterator iter = particleVec.begin(); iter != particleVec.end(); ++iter)
            iter->update(dt);

        // capture pyramid
        //sf::VertexArray pyramidVA = camera.captureLines(pyramidObject);

        /*
        ***************************************
        DRAW TO THE WINDOW
        ***************************************
        */

        // draw stuff to the window each frame
        window.clear();

        //particle1.draw(window, camera);
        //particle2.draw(window, camera);
        drawParticles(particleVec, window, camera);
        //window.draw(pyramidVA);

        window.display();

    } // end main loop

    return 0;
}