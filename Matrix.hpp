#ifndef GUARD__MATRIX_HPP
#define GUARD__MATRIX_HPP
// This class will try to capture the behaviour of a 3x3 matrix

#include "SFML/System/Vector3.hpp"
#include <vector>

class Matrix
{
    friend sf::Vector3f matrixMultiply(const Matrix&, const sf::Vector3f&);
    friend Matrix transpose(const Matrix&);
    friend Matrix inverse(const Matrix&);
    friend float determinant(const Matrix&);

    public:
        Matrix();
        Matrix(const sf::Vector3f&, const sf::Vector3f&, const sf::Vector3f&);
        ~Matrix() {};

        void setRow(int, const sf::Vector3f&);
        void setElement(int, int, const float&);

        float element(int i, int j) const;

        typedef std::vector<float> row;

    private:
        std::vector<row> m_rows;

        float minorDet(int i, int j) const;

};

sf::Vector3f matrixMultiply(const Matrix& matrix, const sf::Vector3f& vec);
// Matrix matrixMultiply(const Matrix&, const Matrix&);
Matrix transpose(const Matrix&);
Matrix inverse(const Matrix&);
float determinant(const Matrix&);



#endif