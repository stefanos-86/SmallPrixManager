#ifndef SPM_TANGENT_CIRCLE
#define SPM_TANGENT_CIRCLE

#include "Math.h"

namespace spm {

    /** In italian is "cerchio osculatore". */
    class TangentCircle {
    public:
        /** Circle passing trough this points. */
        TangentCircle(const Point& p0, const Point& p1, const Point& p2);

        float radius() const;

    private:
        float a, b, c; // Coefficients of the equations.
    };
	
}

#endif