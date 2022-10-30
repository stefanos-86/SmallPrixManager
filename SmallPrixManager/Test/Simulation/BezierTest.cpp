#ifdef TODO_TESTS_DISABLED

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

    TEST(Bezier, atWrongParameter) {
        const Bezier c(Point(0, 0), Point(0, 0.5), Point(0, 9.5), Point(0, 10));

        ASSERT_ANY_THROW(c.at(93));
        ASSERT_ANY_THROW(c.at(-1));
    }


    TEST(Bezier, atLength) {
        const Bezier c(Point(0, 0), Point(0, 0.5), Point(0, 9.5), Point(0, 10));

        ASSERT_EQ(c.at(0.5), Point(0, 5));
        ASSERT_EQ(c.atLength(5), Point(0, 5));
    }



    TEST(Bezier, length) {
        const Bezier c(Point(0, 0), Point(0, 0.5), Point(0, 9.5), Point(0, 10));

        ASSERT_EQ(c.length(), 10);
    }


    TEST(Bezier, curvature) {
        const Bezier c(Point(0, 0), Point(0, 0.5), Point(0, 9.5), Point(0, 10));

        ASSERT_TRUE(std::isinf(c.curvatureRadiusAt(0.5)));

        for (float i = 0; i < 1; i += 0.1f)
            std::cout << c.curvatureRadiusAt(i) << std::endl;

        ASSERT_TRUE(std::isinf(c.curvatureRadiusAt(0)));
    }



    TEST(BezierPath, construction_from_points) {
        const std::vector<Point> points = { { 0, 0 }, { 0, 1 }, { 1, 0 } };
        BezierPath c(points);
        // Complex algo, not sure what to assert!!!
    }

    TEST(BezierPath, construction_insufficient_points) {
        const std::vector<Point> points = { { 0, 0 } };
        ASSERT_ANY_THROW(BezierPath c(points));
    }
}

#endif