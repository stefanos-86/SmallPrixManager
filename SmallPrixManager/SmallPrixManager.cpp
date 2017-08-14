#include "Gui/Gui.h"

#include <stdexcept>
#include <iostream>

/* http://www.kino3d.com/forum/viewtopic.php?f=7&t=8806 ==> Come calcolare la frenata (...come pensavo io!). */

/** Don't forget to install SFML in the PATH:
	PATH=C:\sfml\SFML-2.4.2\bin;%PATH%
*/

#define WITH_TESTS true
#ifdef WITH_TESTS
#include "gtest/gtest.h"
#endif

int main(int argc, char **argv) {
	#ifdef WITH_TESTS
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	#endif

	using namespace spm;

    try {
	    MasterGui gui;
	    gui.mainLoop();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

	return 0;
}

