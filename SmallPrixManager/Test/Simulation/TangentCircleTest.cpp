#ifdef TODO_TESTS_DISABLED

#include "gtest/gtest.h"


#include "../../Simulation/TangentCircle.h"
#include "../../Simulation/Math.h"

namespace spm {
    
	TEST(TangentCircle, centerInOrigin_radiusOne) {
        TangentCircle c(Point(1, 0), Point(0, 1), Point(-1, 0));

		ASSERT_EQ(c.radius(), 1);
	}
}

#endif