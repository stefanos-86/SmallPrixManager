#include "Gui/Gui.h"

/** Non dimenticare che bisogna installare SFML e averla nel PATH:
	PATH=C:\sfml\SFML-2.4.2\bin;%PATH%
*/

int main(void)
{
	using namespace spm;
	MasterGui gui;

	gui.mainLoop();

	return 0;
}

