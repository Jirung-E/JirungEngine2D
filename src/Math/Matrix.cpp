#include "Matrix.h"

#include <assert.h>
#include <stdarg.h>

using namespace std;
using namespace Math;


Matrix::Matrix(int width, int height) : width { width }, height { height } {
    elem = new float*[height];
    for(int i=0; i<height; ++i) {
        elem[i] = new float[width];
        for(int k=0; k<width; ++k) {
            elem[i][k] = 0;
        }
    }
}

Matrix::Matrix(int width, int height, float e1, ...) : width { width }, height { height } {
    va_list args;
    va_start(args, e1);

    elem = new float*[height];
    for(int i=0; i<height; ++i) {
        elem[i] = new float[width];
        for(int k=0; k<width; ++k) {
            if(i == 0 && k == 0) {
                elem[i][k] = e1;
            } else {
                elem[i][k] = va_arg(args, double);
            }
        }
    }

    va_end(args);
}

float& Matrix::operator()(int row, int col) {
    return elem[row][col];
}


Matrix Matrix::operator*(int scalar) const {
    Matrix m { width, height };
    for(int i=0; i<height; ++i) {
        for(int k=0; k<width; ++k) {
            m.elem[i][k] = elem[i][k] * scalar;
        }
    }
    return m;
}

Matrix Matrix::operator*(const Matrix& other) const {
    assert(width == other.height);

    Matrix m { other.width, height };

    float result = 0;
    for(int i=0; i<height; ++i) {
        for(int k=0; k<other.width; ++k) {
            for(int n=0; n<width; ++n) {
                m.elem[i][k] += elem[i][n] * other.elem[n][k];
            }
        }
    }

    return m;
}

Matrix Matrix::operator+(const Matrix& other) const {
    assert(width == other.width);
    assert(height == other.height);

    Matrix m { width, height };
    for(int i=0; i<height; ++i) {
        for(int k=0; k<width; ++k) {
            m.elem[i][k] = elem[i][k] + other.elem[i][k];
        }
    }
    return m;
}

Matrix Matrix::operator-(const Matrix& other) const {
    assert(width == other.width);
    assert(height == other.height);

    Matrix m { width, height };
    for(int i=0; i<height; ++i) {
        for(int k=0; k<width; ++k) {
            m.elem[i][k] = elem[i][k] - other.elem[i][k];
        }
    }
    return m;
}

Matrix Matrix::transpose() const {
    Matrix t { height, width };
    for(int i=0; i<height; ++i) {
        for(int k=0; k<width; ++k) {
            t.elem[k][i] = elem[i][k];
        }
    }
    return t;
}

float Matrix::determinant() const {
    assert(width == height);

    if(width == 1) {
        return elem[0][0];
    }
    if(width == 2) {
        return elem[0][0] * elem[1][1] - elem[0][1] * elem[1][0];
    }

    float det = 0;
    int sign = 1;

    Matrix sub_matrix { width-1, width-1 };

    for(int i=0; i<width; i++) {
        for(int j=1; j<height; j++) {
            int col = 0;
            for(int k=0; k<width; k++) {
                if(k == i) continue;
                sub_matrix.elem[j-1][col++] = elem[j][k];
            }
        }

        det += sign * elem[0][i] * sub_matrix.determinant();
        sign = -sign;
    }

    return det;
}



ostream& Math::operator<<(ostream& os, Matrix m) {
    for(int i=0; i<m.height; ++i) {
        for(int k=0; k<m.width; ++k) {
            os << m(i, k) << " ";
        }
        os << endl;
    }
    return os;
}