#include "Gui.h"

#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>

#include <SFML/Graphics/CircleShape.hpp>

#include "imgui\imgui.h"
#include "imgui\imgui-SFML.h"

#include "PolyLine.h"
#include "BezierAdapter.h"

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

        std::vector<sf::Vector2f> monza = {
            { 521, 562 },
            { 314, 567 },
            { 309, 545 },
            { 256, 568 },
            { 184, 568 },
            { 142, 537 },
            { 108, 477 },
            { 75, 250 },
            { 60, 234 },
            { 17, 90 },
            { 19, 61 },
            { 36, 44 },
            { 108, 26 },
            { 207, 187 },
            { 361, 400 },
            { 396, 400 },
            { 424, 425 },
            { 745, 431 },
            { 773, 448 },
            { 778, 481 },
            { 769, 512 },
            { 748, 537 },
            { 711, 552 },
            { 623, 562 },
            { 521, 562 }  // Repeat first point to close the curve.
        };
        //PolyLine p(monza);
        //window.draw(p);

        BezierPath b(monza);

		ImGui::Begin("Monza!");
		//ImGui::Button("Look at this pretty button");
        static float carPosition = 0;
        ImGui::SliderFloat("Posizione machina", &carPosition, 0, b.length());
		ImGui::End();


		window.clear();
	//	window.draw(shape);
		ImGui::SFML::Render(window);


        BezierAdapter ba(b);
        window.draw(ba);

        sf::CircleShape carShape(5);
        carShape.setFillColor(sf::Color::Red);
        carShape.setPosition(b.atLength(carPosition));
        window.draw(carShape);


		window.display();
	}
}