#include <stdexcept>
#include <iostream>

#include "Simulation\Model.h"
#include "Gui\Gui.h"
#include "Database\Database.h"

/* http://www.kino3d.com/forum/viewtopic.php?f=7&t=8806 ==> Come calcolare la frenata (...come pensavo io! Ma è tosta!).
  Per non parlare dei suggerimenti di alessio (autopilota o problema di CSP).*/

// TODO: reactivate tests (need to create VC++ project for that, or relink gtest as standalone).
// Additional deps where gtest.lib gtest_main - md.lib
#undef WITH_TESTS

// TODO: additional deps on opengl may be not needed.


#ifdef WITH_TESTS  // Defined in debug configuration.
#include "gtest/gtest.h"
#endif

int main(int argc, char **argv) {
	#ifdef WITH_TESTS
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	#endif

	using namespace spm;

    try {
        Model theWorld;
        Database db;
        theWorld.tracks = db.loadTracks("Tracks.xml");
        theWorld.currentTrack = theWorld.tracks.begin(); // This should probably be in a constructor...

	    MasterGui gui(theWorld);
	    gui.mainLoop();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

	return 0;
}

