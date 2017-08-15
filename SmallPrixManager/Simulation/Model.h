#ifndef SPM_MODEL
#define SPM_MODEL

#include <memory>

#include "Track.h"
#include "VehicleDinamic.h"


namespace spm {

	/** Top level interface to give the GUI a single place to find things to display.
    */
	class Model {
    public:

        /** Set up and interconnect the virtual world. 
            The construction of each element may be somewhat complex, so they are kept in pointers
            that can be filled "in their own time", rather than a reference that has to be "made" in the constructor
            initialization list. */
        Model();

        /** Master clock for the simulated work. Calls the updates where needed. 
            The parameter is not const because the slow motion factor may apply. */
        void timeStep(float elapsedSeconds);

        std::shared_ptr<Track> track;
        std::shared_ptr<DynamicCar> car;

        /** The gui uses this to correct the time step. */
        float slowMotion;
    };
}

#endif