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

    Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }


    const float Vector2D::magnitude() const {
        return std::sqrt(x * x + y * y);
    }


    const Vector2D operator+(Vector2D lhs, const Vector2D& rhs) {
        lhs += rhs;
        return lhs;
    }

    const Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs) {
        return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
    }


    const Vector2D operator*(const Vector2D& lhs, const float rhs) {
        return Vector2D(lhs.x * rhs, lhs.y * rhs);
    }


    const Vector2D operator*(const float lhs, const Vector2D& rhs) {
        return rhs * lhs;
    }

    bool operator==(const Point& lhs, const Point& rhs) {
		return lhs.x == rhs.x && 
			   lhs.y == rhs.y;
	}


}