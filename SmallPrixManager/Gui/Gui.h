#ifndef SPM_GUI
#define SPM_GUI


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>


namespace spm {
    class Model;

	class MasterGui {
	public:
		MasterGui(Model& m);
		~MasterGui();
		void mainLoop();

	private:
		void pollEvents();
		void render();

		sf::RenderWindow window;
		sf::Clock deltaClock;

        Model& model;
	};
}

#endif