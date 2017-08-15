#include "Model.h"


namespace spm {
    Model::Model() :
        slowMotion(1)
    {
                std::vector<Point> monza = {
            { 521, 562 },
            { 314, 562 },
            { 309, 562 },
            { 256, 568 },
            { 184, 568 },
            { 142, 537 },
            { 108, 477 },
            { 75, 250 },
            { 60, 234 },
            { 17, 90 },
            { 19, 61 },
            { 36, 44 },
            { 108, 26 },
            { 207, 187 },
            { 361, 400 },
            { 396, 400 },
            { 424, 425 },
            { 745, 431 },
            { 773, 448 },
            { 778, 481 },
            { 769, 512 },
            { 748, 537 },
            { 711, 552 },
            { 623, 562 },
            { 521, 562 }  // Repeat first point to close the curve.
        };


        BezierPath bezierForMonza(monza);


        track = std::make_shared<Track>("Monza", bezierForMonza);

        // Those numbers actually give meaningful results!
        car = std::make_shared<DynamicCar>();
        car->tireBaseFrictionCoefficient = 1;
        car->maximumEnginePower = horsepowerToWatts(700);
        car->airResistanceCoefficient = 0.3;
        car->downforceCoefficient = 0.2;
        car->dryWeight = 600;
        car->speed = 0;
    }


    void Model::timeStep(float elapsedSeconds) {
        elapsedSeconds = elapsedSeconds * slowMotion;
        car->timeStep(elapsedSeconds, track->curvatureRadiusAtCarPosition());
        track->advanceCar(car->speed * elapsedSeconds);
    }

}