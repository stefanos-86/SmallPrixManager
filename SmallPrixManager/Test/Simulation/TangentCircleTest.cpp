#include "gtest/gtest.h"

#include <vector>

#include "../../Simulation/TangentCircle.h"

namespace spm {

	TEST(TangentCircle, centerInOrigin_radiusOne) {
        TangentCircle c(sf::Vector2f(1, 0), sf::Vector2f(0, 1), sf::Vector2f(-1, 0));

		ASSERT_EQ(c.radius(), 1);
	}
}