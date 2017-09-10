#include <stdexcept>
#include <iostream>

#include "Simulation\Model.h"
#include "Gui\Gui.h"
#include "Database\Database.h"

/* http://www.kino3d.com/forum/viewtopic.php?f=7&t=8806 ==> Come calcolare la frenata (...come pensavo io! Ma è tosta!).
  Per non parlare dei suggerimenti di alessio (autopilota o problema di CSP).*/

/** Don't forget to install SFML in the PATH:
	PATH=C:\sfml\SFML-2.4.2\bin;%PATH%
*/

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
        theWorld.track = std::make_shared<Track>(db.loadTracks("Tracks.xml").front());  // For now, one track. Intentional copy here.

	    MasterGui gui(theWorld);
	    gui.mainLoop();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

	return 0;
}

