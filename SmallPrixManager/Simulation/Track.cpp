#include "Track.h"

namespace spm {

    Track::Track(const std::string& name,
                 const BezierPath& trajectory) :
        name(name),
        trajectory(trajectory),
        carPosition(0)
    {};


    const std::string& Track::getName() const {
        return name;
    }


    const float Track::getCarPosition() const {
        return carPosition;
    }

    void Track::setCarPosition(const float position) {
        carPosition = position;
    }

    const Point Track::getCarPoint() const {
        return trajectory.atLength(carPosition);
    }

    void Track::advanceCar(const float meters) {
        carPosition += meters;

        // Across the finish line.
        if (carPosition > trajectory.length())
            carPosition -= trajectory.length();
    }

    float Track::length() const {
        return trajectory.length();
    }

    float Track::curvatureRadiusAtCarPosition() const {
        return trajectory.curvatureRadiusAtLength(carPosition);
    }

    const BezierPath& Track::getTrackCurve() const {
        return trajectory;
    }
 
}