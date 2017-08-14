#include "gtest/gtest.h"

#include "../../Simulation/Track.h"

#include "../../Simulation/Bezier.h"

namespace spm {
    
    TEST(Track, name){
        const std::string trackName("Anything not copyrighted");
        const BezierPath trajectory({{1, 2}, {3, 4}, {5, 6}});

        Track t(trackName, trajectory);
        ASSERT_EQ(trackName, t.getName());
    }

    TEST(Track, carPosition){
        const std::string trackName("Anything not copyrighted");
        const BezierPath trajectory({{1, 2}, {3, 4}, {5, 6}});

        Track t(trackName, trajectory);

        ASSERT_EQ(t.getCarPosition(), 0);
    }


    TEST(Track, advanceCar){
        const std::string trackName("Anything not copyrighted");
        const BezierPath trajectory({{1, 2}, {1522, 4233}});

        Track t(trackName, trajectory);
        t.advanceCar(123);

        ASSERT_EQ(t.getCarPosition(), 123);
    }

    TEST(Track, advanceCar_loop){
        const std::string trackName("Anything not copyrighted");
        const BezierPath trajectory({{0, 0}, {0, 10}});

        // Guard: the trajectory must be 10 meters long.
        ASSERT_FLOAT_EQ(10, trajectory.length());

        Track t(trackName, trajectory);
        t.advanceCar(11);

        ASSERT_EQ(t.getCarPosition(), 1);
    }
	
}