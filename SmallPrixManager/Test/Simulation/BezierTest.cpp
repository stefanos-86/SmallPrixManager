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

    TEST(Bezier, atLength) {
        const Bezier c(sf::Vector2f(0, 0), sf::Vector2f(0, 0.5), sf::Vector2f(0, 9.5), sf::Vector2f(0, 10));

        ASSERT_EQ(c.at(0.5), sf::Vector2f(0, 5));
        ASSERT_EQ(c.atLength(5), sf::Vector2f(0, 5));
    }



    TEST(Bezier, length) {
        const Bezier c(sf::Vector2f(0, 0), sf::Vector2f(0, 0.5), sf::Vector2f(0, 9.5), sf::Vector2f(0, 10));

        ASSERT_EQ(10, c.length());
    }


    TEST(BezierPath, construction_from_points) {
        const std::vector<sf::Vector2f> points = { { 0, 0 }, { 0, 1 }, { 1, 0 } };
        BezierPath c(points);

    }
}