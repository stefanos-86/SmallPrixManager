#include "gtest/gtest.h"

#include <vector>

#include "../../Simulation/Bezier.h"

#include <iostream>

namespace spm {

	TEST(Bezier, construction_straight_segment) {
		const Bezier c(sf::Vector2f(0, 0), sf::Vector2f(0, 0.5), sf::Vector2f(0, 0.5), sf::Vector2f(0, 1));

		ASSERT_EQ(c.at(0), sf::Vector2f(0, 0));
        ASSERT_EQ(c.at(1), sf::Vector2f(0, 1));
        ASSERT_EQ(c.at(0.5), sf::Vector2f(0, 0.5));
	}


    TEST(BezierPath, construction_from_points) {
        const std::vector<sf::Vector2f> points = { { 0, 0 }, { 0, 1 }, { 1, 0 } };
        BezierPath c(points);

    }
}