#include "gtest/gtest.h"

#include "../../Simulation/Bezier.h"


#include <vector>
#include "../../Simulation/Math.h"

namespace spm {
    
	TEST(Bezier, construction_straight_segment) {
		const Bezier c(Point(0, 0), Point(0, 0.5), Point(0, 0.5), Point(0, 1));

		ASSERT_EQ(c.at(0), Point(0, 0));
        ASSERT_EQ(c.at(1), Point(0, 1)); 
        ASSERT_EQ(c.at(0.5), Point(0, 0.5));
	}

    TEST(Bezier, atLength) {
        const Bezier c(Point(0, 0), Point(0, 0.5), Point(0, 9.5), Point(0, 10));

        ASSERT_EQ(c.at(0.5), Point(0, 5));
        ASSERT_EQ(c.atLength(5), Point(0, 5));
    }



    TEST(Bezier, length) {
        const Bezier c(Point(0, 0), Point(0, 0.5), Point(0, 9.5), Point(0, 10));

        ASSERT_EQ(10, c.length());
    }


    TEST(BezierPath, construction_from_points) {
        const std::vector<Point> points = { { 0, 0 }, { 0, 1 }, { 1, 0 } };
        BezierPath c(points);

    }
}