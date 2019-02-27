// source file for the Matrix.hpp header

#include "Matrix.hpp"
#include "vector_operations.hpp"

Matrix::Matrix()
{
    std::vector<float> row;
    for(std::vector<float>::size_type i = 0; i != 3; ++i)
        row.push_back(0.0f);
    

    for(std::vector<float>::size_type i = 0; i != 3; ++i)
        m_rows.push_back(row);
}

Matrix::Matrix(const sf::Vector3f& row1, const sf::Vector3f& row2, const sf::Vector3f& row3)
{
    std::vector<float> row;

    // create the first row
    row.push_back(row1.x);
    row.push_back(row1.y);
    row.push_back(row1.z);
    m_rows.push_back(row);

    // create the next row
    row.clear();
    row.push_back(row2.x);
    row.push_back(row2.y);
    row.push_back(row2.z);
    m_rows.push_back(row);

    // create the next row
    row.clear();
    row.push_back(row3.x);
    row.push_back(row3.y);
    row.push_back(row3.z);
    m_rows.push_back(row);
    
}

void Matrix::setRow(int row, const sf::Vector3f& vec)
{
    m_rows[row].clear();
    m_rows[row].push_back(vec.x);
    m_rows[row].push_back(vec.y);
    m_rows[row].push_back(vec.z);   
}

float Matrix::element(int i, int j) const
{
    return m_rows[i][j];
}

float Matrix::minorDet(int i, int j) const
{
    int rows [2] = {(i + 1) % 3, (i + 2) % 3};
    int cols [2] = {(j + 1) % 3, (j + 2) % 3};

    return m_rows[rows[0]][cols[0]] * m_rows[rows[1]][cols[1]] - m_rows[rows[1]][cols[0]] * m_rows[rows[0]][cols[1]];
}

void Matrix::setElement(int row, int col, const float& val)
{
    m_rows[row][col] = val;
}

sf::Vector3f matrixMultiply(const Matrix& matrix, const sf::Vector3f& vec)
{
    return sf::Vector3f(
        dot(sf::Vector3f(matrix.m_rows[0][0], matrix.m_rows[0][1], matrix.m_rows[0][2]), vec),
        dot(sf::Vector3f(matrix.m_rows[1][0], matrix.m_rows[1][1], matrix.m_rows[1][2]), vec),
        dot(sf::Vector3f(matrix.m_rows[2][0], matrix.m_rows[2][1], matrix.m_rows[2][2]), vec)
    );
}

Matrix transpose(const Matrix& m)
{
    Matrix ret;

    for(int i = 0; i != 3; ++i)
    {
        for(int j = 0; j != 3; ++j)
        {
            ret.setElement(i, j, m.element(j, i));
        }
    }


    return ret;
}

float determinant(const Matrix& m)
{
    return  m.m_rows[0][0] * m.minorDet(0, 0) 
            + m.m_rows[0][1] * m.minorDet(0, 1) 
            + m.m_rows[0][2] * m.minorDet(0, 2);
}

Matrix inverse(const Matrix& m)
{
    Matrix ret;

    float det = determinant(m);

    for(int i = 0; i != 3; ++i)
    {
        for(int j = 0; j != 3; ++j)
        {
            ret.setElement(i, j, m.minorDet(i, j) / det);
        }
    }
    
    ret = transpose(ret);

    return ret;
}

