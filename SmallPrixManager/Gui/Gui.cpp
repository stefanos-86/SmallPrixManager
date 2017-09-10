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
            simulate(clock.restart().asSeconds());
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

		ImGui::Begin(model.currentTrack->getName().c_str());
        /*
        static float carPosition = 0;
        ImGui::SliderFloat("Posizione machina", &carPosition, 0, model.track->length());
        model.track->setCarPosition(carPosition); */

        ImGui::SliderFloat("Slow motion", &model.slowMotion, 0, 2);
        ImGui::Text("Velocita' (Km/h) %f", model.car->speed * 3.6);
        float radius = model.currentTrack->curvatureRadiusAtCarPosition();
        if (isinf(radius))
            ImGui::Text("Rettilineo");
        else {
            ImGui::Text("Raggio curva %f", radius);
        }

		ImGui::End();

		window.clear();
		ImGui::SFML::Render(window);

        BezierAdapter ba(model.currentTrack->getTrackCurve());
        window.draw(ba);

        sf::CircleShape carShape(5);
        carShape.setFillColor(sf::Color::Red);
        carShape.setPosition(toGraphic(model.currentTrack->getCarPoint()));
        window.draw(carShape);


		window.display();
	}


    void MasterGui::simulate(const float elapsedSeconds) {
        model.timeStep(elapsedSeconds);
    }
}