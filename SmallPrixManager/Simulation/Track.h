#ifndef SPM_TRACK
#define SPM_TRACK

#include <string>

#include "Bezier.h"

namespace spm {

    class Track {
    public:
        Track(const std::string& name,
              const BezierPath& trajectory);

        const std::string& getName();

        /** Return the position of the car along the track.
            0 means it is at the start/finish line.
            Any other "x" means it started and made x meters after the start line along the trajectory. */
        const float getCarPosition() const;

        /** Move the cars ahead the specified amount of meters. 
            Takes into account that we have a circuit, the position "goes back" when the car
            goes across the finish line. The advancement is supposed to be less than a lap. */
        void advanceCar(const float meters);

    private:
        /** Label just to know where we are racing. */
        const std::string name;

        /** Path that the cars move along.
            (From a direct translation of "traiettoria". The English jargon may differ.) */
        const BezierPath trajectory;

        /** Where the car is along the path. */
        float carPosition;
    };
}

#endif