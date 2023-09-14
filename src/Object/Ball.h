#ifndef __Ball_h__
#define __Ball_h__

#include "Object.h"


namespace JirungEngine {
    class Ball : public Object {
    public:
        float radius;

    public:
        Ball(const Math::Point& center, float radius);
    };
}

#endif
