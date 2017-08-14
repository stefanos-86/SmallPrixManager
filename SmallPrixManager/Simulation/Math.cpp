#include "Math.h"

#include <cmath>

namespace spm {

    Vector2D::Vector2D() :
        x(0), y(0) {}

    Vector2D::Vector2D(const float x, const float y):
        x(x), y(y) {} 

    void Vector2D::normalize() {
        const float length = magnitude();
        x /= length;
        y /= length;
    }


    const float Vector2D::magnitude() const {
        return std::sqrt(x * x + y * y);
    }


    const Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) {
        return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
    }


}