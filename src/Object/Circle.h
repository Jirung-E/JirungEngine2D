#ifndef __Circle_h__
#define __Circle_h__

#include "Object.h"


namespace JirungEngine {
    class Circle : public Object {
    public:
        float radius;

    public:
        Circle(const Math::Point& center, float radius);
    };
}

#endif
