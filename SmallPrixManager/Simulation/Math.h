#ifndef SPM_MATH
#define SPM_MATH

#include <vector>

namespace spm {

	/** Toolbox with a miscellanea of mathematical utilities.
        This project does not use enough math to justify linking a real library.
        SFML does not have expose its internal math, so no way to recycle. */
	
    class Vector2D {
    public:
        float x;
        float y;

        Vector2D();
        Vector2D(const float x, const float y);

        void normalize();
        const float magnitude() const;
    };


    const Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
}

#endif