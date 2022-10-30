#include "VehicleDinamic.h"

#include <cmath>

namespace spm {
    static const float WATTS_PER_HORSEPOWER = 735.49875f;
    static const float G = 9.81f;

    float horsepowerToWatts(const float horsepower) {
        return WATTS_PER_HORSEPOWER * horsepower;
    }

    float wattsToHorsepower(const float watts) {
        return watts / WATTS_PER_HORSEPOWER;
    }
 

    void DynamicCar::timeStep(const float deltaT, const float trajectoryCurvatureRadius) {
        const float downforce = speed * speed * downforceCoefficient;
        const float maxGeometrySpeed = std::sqrt((tireBaseFrictionCoefficient * trajectoryCurvatureRadius * (G * dryWeight + downforce)) / dryWeight);

        const float airResistance = computeAirResistance();
        const float previousEnergy = 0.5f * dryWeight * speed * speed;
        const float currentEnergy = previousEnergy + (maximumEnginePower - airResistance) * deltaT;
        const float maxMechanicalSpeed = std::sqrt(2 * currentEnergy / dryWeight);
        
        speed = std::fmin(maxGeometrySpeed, maxMechanicalSpeed);

    }


    float DynamicCar::computeAirResistance() const {
        if (speed < 8.5)  // More or less 30 Km/h
            return airResistanceCoefficient * speed;
        else
            return airResistanceCoefficient * speed * speed * speed;
    }
}