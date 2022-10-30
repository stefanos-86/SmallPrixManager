#ifndef SPM_MATH
#define SPM_MATH

#include <vector>

namespace spm {

	/** Toolbox with a miscellanea of mathematical utilities.
        This project does not use enough math to justify linking a real library.
        SFML does not have expose its internal math, so no way to recycle. 
        
        This file provides just enough operators as needed, not a complete interface. 
        
        Canonical forms of the operators are here:
        http://en.cppreference.com/w/cpp/language/operators
    */
	
    class Vector2D {
    public:
        float x;
        float y;

        Vector2D();
        Vector2D(const float x, const float y);

        void normalize();
        const float magnitude() const;

        Vector2D& operator+=(const Vector2D& rhs);
    };


    const Vector2D operator+(Vector2D lhs, const Vector2D& rhs);
    const Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
    const Vector2D operator*(const Vector2D& lhs, const float rhs);
    const Vector2D operator*(const float lhs, const Vector2D& rhs);

    bool operator==(const Vector2D& lhs, const Vector2D& rhs);
    
    /** Alias that helps keep function signatures clean. */
    typedef Vector2D Point;
}

#endif