#include "Object.h"

using namespace JirungEngine;


Object::Object(const Math::Point& position) : position { position }, mass { 0.0f } {

}

Object::Object() : Object { { 0, 0, 0 } } {

}


void JirungEngine::Object::update() {
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;

    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
    velocity.z += acceleration.z;


}
