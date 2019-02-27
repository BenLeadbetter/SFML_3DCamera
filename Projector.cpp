// source file for the Projector.hpp header

#include "Projector.hpp"
#include "vector_operations.hpp"

sf::Vector3f Projector::bringToProjectionPlane(const sf::Vector3f& vec) const
{
    // find the vector line parameter
    float lambda = (m_CameraZoom - dot(m_CameraDirection, vec)) / dot(m_CameraDirection, m_CameraPosition - vec);

    // return the correct point on the vector line
    return vec + lambda * (m_CameraPosition - vec);
}

void Projector::generateMatrix()
{   
    // obtain the first basis vector
    sf::Vector3f projectedOrigin = bringToProjectionPlane(sf::Vector3f(0, 0, 0));
    sf::Vector3f e2 = bringToProjectionPlane(sf::Vector3f(0, 0, 1)) - projectedOrigin;
    // normalise
    e2 = unitVector(e2);
    // stipulate the seecond perp to the first
    sf::Vector3f e1 = cross(m_CameraDirection, e2);
    // normalise
    e1 = unitVector(e1);
    

    // now assemble the matrix
    Matrix basisChange;
    basisChange.setRow(0, e1);
    basisChange.setRow(1, m_CameraDirection);
    basisChange.setRow(2, e2);
    basisChange = transpose(basisChange);
    m_BasisChange = inverse(basisChange);

}

void Projector::generateMatrix(sf::Vector3f disp)
{   
    // obtain the first basis vector
    sf::Vector3f projectedOrigin = bringToProjectionPlane(sf::Vector3f(0, 0, 0) + disp);
    sf::Vector3f e2 = bringToProjectionPlane(sf::Vector3f(0, 0, 1) + disp) - projectedOrigin;
    // normalise
    e2 = unitVector(e2);
    // stipulate the seecond perp to the first
    sf::Vector3f e1 = cross(m_CameraDirection, e2);
    // normalise
    e1 = unitVector(e1);
    

    // now assemble the matrix
    Matrix basisChange;
    basisChange.setRow(0, e1);
    basisChange.setRow(1, m_CameraDirection);
    basisChange.setRow(2, e2);
    basisChange = transpose(basisChange);
    m_BasisChange = inverse(basisChange);

}


Projector::Projector(const sf::Vector3f& cameraPos, const sf::Vector3f& cameraDir, const float& zoom)
{
    m_CameraPosition = cameraPos;
    m_CameraDirection = unitVector(cameraDir);
    m_CameraZoom = zoom;

    // Set up the basis change matrix
    generateMatrix();

}

void Projector::setCameraDir(const sf::Vector3f& cameraDir)
{
    // reset the member variable
    m_CameraDirection = unitVector(cameraDir);

    // regenerate the matrix
    generateMatrix();
}

void Projector::setCameraDir(const sf::Vector3f& cameraDir, const sf::Vector3f& disp)
{
    // reset the member variable
    m_CameraDirection = unitVector(cameraDir);

    // regenerate the matrix
    generateMatrix(disp);
}

void Projector::setCameraPos(const sf::Vector3f& cameraPos)
{
    // reset the member variable
    m_CameraPosition = cameraPos;

    // regenerate the matrix
    generateMatrix();
}

void Projector::setCameraPos(const sf::Vector3f& cameraPos, const sf::Vector3f& disp)
{
    // reset the member variable
    m_CameraPosition = cameraPos;

    // regenerate the matrix
    generateMatrix(disp);
}

void Projector::setZoom(const float& zoom)
{
    // reset the member variable
    m_CameraZoom = zoom;

    // regenerate the matrix
    generateMatrix();  
}

void Projector::setZoom(const float& zoom, const sf::Vector3f& disp)
{
    // reset the member variable
    m_CameraZoom = zoom;

    // regenerate the matrix
    generateMatrix(disp);  
}

sf::Vector2f Projector::project(const sf::Vector3f& vec) const
{
    // first we bring the point to the projection plane
    sf::Vector3f point = bringToProjectionPlane(vec);

    // then we change the basis
    point = matrixMultiply(m_BasisChange, point);

    // capture the correct coordinates and flip
    sf::Vector2f ret(-point.x, -point.z);

    // centralise the image on the screen
    // ************ need to make this dynamic
    ret += sf::Vector2f(500, 400);

    // return the vector
    return ret;

}