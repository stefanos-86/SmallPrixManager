#include "Gui.h"

#include <memory>
#include <array>
#include <algorithm>
#include <stdexcept>

#define SDL_MAIN_HANDLED
#include <SDL.h>
//#undef main  // https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc

#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include "imgui\imgui_impl_sdlrenderer.h"

#include "PolyLine.h"
#include "BezierAdapter.h"

#include "../Simulation/Model.h"
#include "PointConversion.h"

namespace spm {
    MasterGui::MasterGui(Model& m) :
        model(m),
        haltMainLoop(false)
    {
        SDL_SetMainReady();

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            printf("Error: %s\n", SDL_GetError());
            throw std::runtime_error("SDL error");
        }

        // Setup window
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        SDL_Window* window = SDL_CreateWindow("Small Prix Manager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, window_flags);

        // Setup SDL_Renderer instance
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            SDL_Log("Error creating SDL_Renderer!");
            throw std::runtime_error("SDL error");
        }
        SDL_RendererInfo info;
        SDL_GetRendererInfo(renderer, &info);
        SDL_Log("Current SDL_Renderer: %s", info.name);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer_Init(renderer);

        trackSelector.fill(false);
    }

	MasterGui::~MasterGui() {
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
	}

	void MasterGui::mainLoop() {
		while (!haltMainLoop) {
			pollEvents();
            simulate(1); // TODO: elapsed seconds.
			render();
		}
	}

	void MasterGui::pollEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                haltMainLoop = true;
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            {
                haltMainLoop = true;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                haltMainLoop = true;
            }
            // TODO: window resize.
        }

        if (haltMainLoop)
            return;
		

        // Deal with track selections
        const auto selectedTrack = std::find(std::begin(trackSelector),
                                                std::end(trackSelector),
                                                true);
        const auto selectionPosition = selectedTrack - std::begin(trackSelector);
        if (selectionPosition < 50 && model.currentTrack->getName() != model.tracks.at(selectionPosition).getName()){
            model.currentTrack = model.tracks.begin() + selectionPosition;
        }

        trackSelector.fill(false);  // Reset for next time.
	}

	void MasterGui::render() {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

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

        if (ImGui::BeginMenu("Tracks")) {
            size_t trackCounter = 0;
            for (const Track& track : model.tracks)
            {
                ImGui::MenuItem(track.getName().c_str(), nullptr, &trackSelector[trackCounter], &trackSelector[trackCounter]);
                trackCounter++;
            }
        
            ImGui::EndMenu();
        }
		ImGui::End();

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);

        /*
        * 
        * TODO: port to SDL
        BezierAdapter ba(model.currentTrack->getTrackCurve());
        window.draw(ba);

        sf::CircleShape carShape(5);
        carShape.setFillColor(sf::Color::Red);
        carShape.setPosition(toGraphic(model.currentTrack->getCarPoint()));
        window.draw(carShape);
         

		window.display();
        */
	}


    void MasterGui::simulate(const float elapsedSeconds) {
        model.timeStep(elapsedSeconds);
    }
}