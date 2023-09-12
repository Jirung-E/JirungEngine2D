#include "../Math.h"

#include <assert.h>
#include <iostream>


namespace Math {
    void testPoint() {
        using namespace Math;
        using namespace std;

        cout << "Point test" << endl;

        Point v1 { 1.0f, 2.0f, 3.0f };
        Point v2 { 2.0f, 3.0f, 4.0f };
        assert(v1 == v1);
        assert(v1 + v2 == Point(3.0f, 5.0f, 7.0f));
        assert(v1 - v2 == Point(-1.0f, -1.0f, -1.0f));
        assert(v1 * 2.0f == Point(2.0f, 4.0f, 6.0f));
        assert(v1 / 2.0f == Point(0.5f, 1.0f, 1.5f));
        assert(v1 != v2);

        Point v1_copy = v1;
        assert(v1_copy == v1);
        assert((v1_copy += v2) == Point(3.0f, 5.0f, 7.0f));
        assert((v1_copy -= v2) == Point(1.0f, 2.0f, 3.0f));
        assert((v1_copy *= 2.0f) == Point(2.0f, 4.0f, 6.0f));
        assert((v1_copy /= 2.0f) == Point(1.0f, 2.0f, 3.0f));

        assert(v1 * 2.0f * 3.0f == Point(6.0f, 12.0f, 18.0f));
        assert(v1 / 2.0f / 3.0f == v1 / 6.0f);
        assert(v1 + v2 + v1_copy == Point(4.0f, 7.0f, 10.0f));
        assert(v1 - v2 - v1_copy == Point(-2.0f, -3.0f, -4.0f));
        assert(v1 + v2 * 2.0f == Point(5.0f, 8.0f, 11.0f));
        assert(v1 - v2 * 2.0f == Point(-3.0f, -4.0f, -5.0f));

        assert(distanceBetween(v1, v2) == sqrt(3.0f));
        assert(distanceBetween(v2, v1) == sqrt(3.0f));

        cout << "test passed" << endl << endl;
    }

    void testVector() {
        using namespace Math;
        using namespace std;

        cout << "Vector test" << endl;

        Vector v1 { 1.0f, 2.0f, 3.0f };
        Vector v2 { 2.0f, 3.0f, 4.0f };
        assert(v1 == v1);
        assert(v1 + v2 == Vector(3.0f, 5.0f, 7.0f));
        assert(v1 - v2 == Vector(-1.0f, -1.0f, -1.0f));
        assert(v1 * 2.0f == Vector(2.0f, 4.0f, 6.0f));
        assert(v1 / 2.0f == Vector(0.5f, 1.0f, 1.5f));
        assert(v1 != v2);

        Vector v1_copy = v1;
        assert(v1_copy == v1);
        assert((v1_copy += v2) == Vector(3.0f, 5.0f, 7.0f));
        assert((v1_copy -= v2) == Vector(1.0f, 2.0f, 3.0f));
        assert((v1_copy *= 2.0f) == Vector(2.0f, 4.0f, 6.0f));
        assert((v1_copy /= 2.0f) == Vector(1.0f, 2.0f, 3.0f));

        assert(-v1 == Vector(-1.0f, -2.0f, -3.0f));

        assert(v1 * 2.0f * 3.0f == Vector(6.0f, 12.0f, 18.0f));
        assert(v1 / 2.0f / 3.0f == v1 / 6.0f);
        assert(v1 + v2 + v1_copy == Vector(4.0f, 7.0f, 10.0f));
        assert(v1 - v2 - v1_copy == Vector(-2.0f, -3.0f, -4.0f));
        assert(v1 * 2.0f * v2 == 40.0f);
        assert(v1 + v2 * 2.0f == Vector(5.0f, 8.0f, 11.0f));
        assert(v1 - v2 * 2.0f == Vector(-3.0f, -4.0f, -5.0f));

        assert(v1.cross(v2) == Vector(-1.0f, 2.0f, -1.0f));
        assert(v2.cross(v1) == Vector(1.0f, -2.0f, 1.0f));

        Vector v3 { 10.0f, 20.0f, 30.0f };
        assert(isParallel(v1, v3));
        assert(!isParallel(v1, v2));
        assert(isOrthogonal(v1, Vector { -1.0f, 2.0f, -1.0f }));
        assert(!isOrthogonal(v1, v2));

        cout << "test passed" << endl << endl;
    }

    void testMatrix() {
        using namespace Math;
        using namespace std;

        cout << "Matrix test" << endl;

        Matrix m1 { 2, 2,
            1.0, 2.0,
            3.0, 4.0
        };
        Matrix m2 { 2, 2 };
        m2(0, 0) = 5;
        m2(0, 1) = 6;
        m2(1, 0) = 7;
        m2(1, 1) = 8;

        cout << m1 << endl;
        cout << m2 << endl;

        cout << m1 * m2 << endl;

        cout << endl;

        cout << "m1(1, 0): " << m1(1, 0) << endl;
        cout << "m1_trans(1, 0): " << m1.transpose()(1, 0) << endl;
        cout << "m1.det(): " << m1.determinant() << endl;

        //cout << "test passed" << endl << endl;
    }
}