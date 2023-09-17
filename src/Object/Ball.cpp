#include "Ball.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace JirungEngine;


Ball::Ball(const Math::Point& center, float radius) : Object { center }, 
    radius { radius } {
    mass = 4.0f/3.0f * M_PI * radius*radius*radius;
}
