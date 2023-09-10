#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <ostream>


namespace Math {
    class Matrix {
    public:
        const int width;
        const int height;

    private:
        float** elem;

    public:
        Matrix(int width, int height);
        Matrix(int width, int height, float e1, ...);
        float& operator()(int row, int col);

    public:
        Matrix operator*(int scalar) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;

        Matrix transpose() const;
        float determinant() const;
    };

    std::ostream& operator<<(std::ostream& os, Matrix m);
}

#endif