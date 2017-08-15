#ifndef SPM_MODEL
#define SPM_MODEL

#include <memory>

#include "Track.h"

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

        std::shared_ptr<Track> track;
    };
}

#endif