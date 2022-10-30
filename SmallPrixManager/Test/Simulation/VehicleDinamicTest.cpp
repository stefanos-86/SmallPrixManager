#ifdef TODO_TESTS_DISABLED

#include "gtest/gtest.h"

#include "../../Simulation/VehicleDinamic.h"

namespace spm {

TEST(free_functions, horsepowerToWatts) {
    ASSERT_FLOAT_EQ(horsepowerToWatts(1), 735.49875f);
}

TEST(free_functions, wattsToHorsepower) {
    ASSERT_FLOAT_EQ(wattsToHorsepower(735.49875f), 1);
}
    
TEST(DynamicCar, unit_car) {
    DynamicCar d;
    d.tireBaseFrictionCoefficient = 1;
    d.maximumEnginePower = 1;
    d.airResistanceCoefficient = 1;
    d.downforceCoefficient = 1;
    d.dryWeight = 1;

    d.speed = 0;

    d.timeStep(1, 1);

    ASSERT_FLOAT_EQ(d.speed, 1.4142135f);
}

}

#endif