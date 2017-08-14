#include "Track.h"

namespace spm {

    Track::Track(const std::string& name,
                 const BezierPath& trajectory) :
        name(name),
        trajectory(trajectory),
        carPosition(0)
    {};


    const std::string& Track::getName() {
        return name;
    }


    const float Track::getCarPosition() const {
        return carPosition;
    }

    void Track::advanceCar(const float meters) {
        carPosition += meters;

        // Across the finish line.
        if (carPosition > trajectory.length())
            carPosition -= trajectory.length();
    }
 
}