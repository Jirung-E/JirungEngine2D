#include "Object.h"

using namespace JirungEngine;


Object::Object(const Math::Point& position) : position { position }, mass { 0.0f } {

}

Object::Object() : Object { { 0, 0, 0 } } {

}


void JirungEngine::Object::update(float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;

    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    velocity.z += acceleration.z * dt;


}
