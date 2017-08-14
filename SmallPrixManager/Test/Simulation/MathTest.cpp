#include "gtest/gtest.h"

#include <vector>

#include "../../Simulation/Math.h"


namespace spm {

	TEST(Vector2D, empty_construction) {
        const Vector2D v;

		ASSERT_EQ(v.x, 0);
        ASSERT_EQ(v.y, 0); 
	}

    TEST(Vector2D, construct_with_params) {
        const Vector2D v(1, 2);

        ASSERT_EQ(v.x, 1);
        ASSERT_EQ(v.y, 2);
    }

    TEST(Vector2D, magnitude) {
        const Vector2D v(1, 0);

        ASSERT_EQ(v.magnitude(), 1);
    }

    TEST(Vector2D, normalize) {
        Vector2D v(152, 0);
        v.normalize();

        ASSERT_EQ(v.x, 1);
    }

    TEST(Vector2D, difference) {
        const Vector2D a(86, 12);
        const Vector2D b(65, 7);
        
        const Vector2D diff = a - b;

        ASSERT_EQ(diff.x, 21);
        ASSERT_EQ(diff.y, 5);
    }

}