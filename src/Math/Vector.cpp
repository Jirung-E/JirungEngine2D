#include "Vector.h"

#include <cmath>

using namespace Math;


Vector::Vector(float x, float y, float z) : x { x }, y { y }, z { z } {

}

Vector::Vector(const Vector& vector) : Vector { vector.x, vector.y, vector.z } {

}

Vector::Vector() : Vector { 0, 0, 0 } {

}


Vector Vector::operator+(const Vector& vector) const {
    return Vector { x + vector.x, y + vector.y, z + vector.z };
}

Vector Vector::operator-(const Vector& vector) const {
    return Vector { x - vector.x, y - vector.y, z - vector.z };
}

float Vector::operator*(const Vector& vector) const {
    return x*vector.x + y*vector.y + z*vector.z;
}


Vector Vector::operator*(float n) const {
    return Vector { x*n, y*n, z*n };
}

Vector Vector::operator/(float n) const {
    return Vector { x/n, y/n, z/n };
}


Vector Vector::operator-() {
    return (*this) * -1;
}


Vector& Vector::operator+=(const Vector& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& vector) {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

Vector& Vector::operator*=(float n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

Vector& Vector::operator/=(float n) {
    x /= n;
    y /= n;
    z /= n;
    return *this;
}


bool Vector::operator==(const Vector& vector) const {
    if(x == vector.x && y == vector.y && z == vector.z) {
        return true;
    }
    return false;
}

bool Vector::operator!=(const Vector& vector) const {
    return !(*this == vector);
}


Vector Vector::cross(const Vector& vector) const {
    return Vector { y*vector.z - z*vector.y, z*vector.x - x*vector.z, x*vector.y - y*vector.x };
}

float Vector::magnitude() const {
    return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
}


float Math::angleBetween(const Vector& vector1, const Vector& vector2) {
    if(vector1.magnitude() == 0 || vector2.magnitude() == 0) {
        return 0.0f;
    }
    return acos((vector1 * vector2) / (vector1.magnitude() * vector2.magnitude()));
}


bool Math::isParallel(const Vector& vector1, const Vector& vector2) {
    //Vector u1 = vector1 / vector1.magnitude();
    //Vector u2 = vector2 / vector2.magnitude();        --> 이렇게 하면 실수 표현 한계 때문에 안맞을때도 있음
    //return u1 == u2 || u1 == -u2;
    return vector1.x / vector2.x == vector1.y / vector2.y && vector1.y / vector2.y == vector1.z / vector2.z;
}

bool Math::isOrthogonal(const Vector& vector1, const Vector& vector2) {
    return vector1 * vector2 == 0.0f;
}


std::ostream& Math::operator<<(std::ostream& os, Vector v) {
    os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
    return os;
}
