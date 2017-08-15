#include "Gui.h"

#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>

#include <SFML/Graphics/CircleShape.hpp>

#include "imgui\imgui.h"
#include "imgui\imgui-SFML.h"

#include "PolyLine.h"
#include "BezierAdapter.h"

#include "../Simulation/Model.h"
#include "PointConversion.h"

namespace spm {
	MasterGui::MasterGui(Model& m) :
		window(sf::VideoMode(800, 600), "SmallPrixManager", sf::Style::Default), model(m)
		{
			window.setVerticalSyncEnabled(true);
			window.setFramerateLimit(60);
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

			/*else if (event.type == sf::Event::MouseMoved)
			    Mouse delegated to imgui.*/

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
		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin(model.track->getName().c_str());
        static float carPosition = 0;
        ImGui::SliderFloat("Posizione machina", &carPosition, 0, model.track->length());
        model.track->setCarPosition(carPosition);

        float radius = model.track->curvatureRadiusAtCarPosition();
        if (isinf(radius))
            ImGui::Text("Rettilineo");
        else {
            ImGui::Text("Raggio curva %f", radius);
            ImGui::Text("v max %f", sqrt(9.81 * abs(radius)));
            // Info utili sull'attrito: http://www.hwupgrade.it/forum/archive/index.php/t-900763.html
        }
		ImGui::End();

		window.clear();
		ImGui::SFML::Render(window);

        BezierAdapter ba(model.track->getTrackCurve());
        window.draw(ba);

        sf::CircleShape carShape(5);
        carShape.setFillColor(sf::Color::Red);
        carShape.setPosition(toGraphic(model.track->getCarPoint()));
        window.draw(carShape);


		window.display();
	}
}