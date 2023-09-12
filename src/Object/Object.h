#ifndef __Object_h__
#define __Object_h__

#include "../Math/Point.h"
#include "../Math/Vector.h"


namespace JirungEngine {
    class Object {
    public:
        Math::Point position;
        Math::Vector velocity;
        Math::Vector acceleration;
        float mass;

    public:
        Object(const Math::Point& position);
        Object();

    public:
        virtual void update();

    };
}

#endif