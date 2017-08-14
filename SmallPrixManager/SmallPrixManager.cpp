#include "Gui/Gui.h"

/** Non dimenticare che bisogna installare SFML e averla nel PATH:
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
	MasterGui gui;
	gui.mainLoop();

	return 0;
}

