#include "Model.h"


namespace spm {
    Model::Model() :
        slowMotion(1)
    {
        // Those numbers actually give meaningful results!
        car = std::make_shared<DynamicCar>();
        car->tireBaseFrictionCoefficient = 1;
        car->maximumEnginePower = horsepowerToWatts(700);
        car->airResistanceCoefficient = 0.3f;
        car->downforceCoefficient = 0.2f;
        car->dryWeight = 600;
        car->speed = 0;
    }


    void Model::timeStep(float elapsedSeconds) {
        elapsedSeconds = elapsedSeconds * slowMotion;
        car->timeStep(elapsedSeconds, currentTrack->curvatureRadiusAtCarPosition());
        currentTrack->advanceCar(car->speed * elapsedSeconds);
    }

}