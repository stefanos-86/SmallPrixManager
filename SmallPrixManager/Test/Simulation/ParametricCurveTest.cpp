#include "gtest/gtest.h"

#include <vector>

#include "../../Simulation/ParametricCurve.h"

namespace spm {

	TEST(ParametricCurve, construction_unitary_segment) {
		std::vector < float > unitarySegment = {0, 0, 0, 1};
		ParametricCurve c(unitarySegment);

		/*ASSERT_EQ(c.at(0), Point(0, 0, 0));
		ASSERT_EQ(c.at(1), Point(0, 1, 1));*/
	}
}