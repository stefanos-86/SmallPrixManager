#include "Gui.h"

#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>

#include "imgui\imgui.h"
#include "imgui\imgui-SFML.h"

namespace spm {
	MasterGui::MasterGui() :
		window(sf::VideoMode(800, 600), "SmallPrixManager", sf::Style::Default)
		{
			window.setVerticalSyncEnabled(true);
			//window.setFramerateLimit(60);
			sf::ContextSettings settings = window.getSettings();
			ImGui::SFML::Init(window);
		}

	MasterGui::~MasterGui() {
		ImGui::SFML::Shutdown();
	}

	void MasterGui::mainLoop() {
		sf::Clock clock;
		while (window.isOpen()) {
			pollEvents();
			render();
		}
	}

	void MasterGui::pollEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			/*else if (event.type == sf::Event::MouseMoved) {
			...si, mo me metto pure a fa' er mouse.
			}*/

			else if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}

			ImGui::SFML::ProcessEvent(event);
		}
	}

	void MasterGui::render() {

		/*sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);*/
		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();

		window.clear();
	//	window.draw(shape);
		ImGui::SFML::Render(window);
		window.display();
	}
}