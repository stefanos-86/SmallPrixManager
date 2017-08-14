#ifndef SPM_GUI
#define SPM_GUI


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace spm {

	class MasterGui {
	public:
		MasterGui();
		~MasterGui();
		void mainLoop();

	private:
		void pollEvents();
		void render();

		sf::RenderWindow window;
		sf::Clock deltaClock;

	};
}

#endif