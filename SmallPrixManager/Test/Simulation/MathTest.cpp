#ifdef TODO_TESTS_DISABLED


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


    TEST(Vector2D, compound_sum) {
        Vector2D a(0, 0);
        const Vector2D b(1, 2);
        
        a += b;

        ASSERT_EQ(a.x, 1);
        ASSERT_EQ(a.y, 2);
    }


    TEST(Vector2D, sum) {
        Vector2D a(0, 0);
        const Vector2D b(1, 2);
        
        const Vector2D c = a + b;

        ASSERT_EQ(c.x, 1);
        ASSERT_EQ(c.y, 2);
    }



    TEST(Vector2D, difference) {
        const Vector2D a(86, 12);
        const Vector2D b(65, 7);
        
        const Vector2D diff = a - b;

        ASSERT_EQ(diff.x, 21);
        ASSERT_EQ(diff.y, 5);
    }


    TEST(Vector2D, product_with_scalar) {
        const Vector2D v(1, 0);
        
        const Vector2D doubleV = v * 2;

        ASSERT_EQ(doubleV.x, 2);
    }

    TEST(Vector2D, product_with_scalar_commutation) {
        const Vector2D v(1, 0);
        
        const Vector2D doubleV = 2 * v;

        ASSERT_EQ(doubleV.x, 2);
    }

    TEST(Vector2D, equality) {
        const Vector2D v(1, 0);
        
        ASSERT_EQ(v, v);
    }
}

#endif