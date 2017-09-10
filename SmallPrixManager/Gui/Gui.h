#ifndef SPM_GUI
#define SPM_GUI

#include <array>

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
        void simulate(const float elapsedSeconds);

		sf::RenderWindow window;
		sf::Clock deltaClock;

        Model& model;

        /** Booleans to be filled to get the selected track. 
            I don't expect more than 50 tracks. This is a parallel
            array with the tracks in the model. */
        std::array<bool, 50> trackSelector;
	};
}

#endif