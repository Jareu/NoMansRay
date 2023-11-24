// NoMansRay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(push, 0)
#pragma warning( disable : 4468 )
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#pragma warning(pop)
#undef main

#include <stdlib.h>     /* srand, rand */
#include <iostream>

#include "globals.h"
#include "types.h"
#include "graphics.h"

#include <box2d.h>
#include "Universe.h"
#include <memory>
#include "Asteroid.h"
#include "SpaceShip.h"
#include "maths.h"
#include "IAudioManager.h"
#include "AudioManagerFactory.h"
#include "NoiseTest.h"

int		main();
void	handleEvents();
void	update();
int		render();

auto universe = std::make_unique<Universe>(1234);
std::unique_ptr<IAudioManager> audio_manager;

int main()
{
	{
		auto noise_test = NoiseTest();
		noise_test.test();
	}

	int SDL_RENDERER_FLAGS = 0;
	int SDL_WINDOW_INDEX = -1;

	int SDL_WINDOW_FLAGS = 0;
	SDL_WINDOW_FLAGS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;

	if (is_fullscreen) {
		SDL_WINDOW_FLAGS = SDL_WINDOW_FLAGS | SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		// SDL failed. Output error message and exit
		std::cout << "Failed to initialize SDL:" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	// Create Window
	window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FLAGS);
	if (!window) {
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	// set window size
	SDL_SetWindowMinimumSize(window, 100, 100);
	SDL_GetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

	// Create Renderer
	renderer = SDL_CreateRenderer(window, SDL_WINDOW_INDEX, SDL_RENDERER_FLAGS);
	if (!renderer) {
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	audio_manager = AudioManagerFactory::createAudioManager();

	audio_manager->initMixer();

	int music = audio_manager->loadMusic("audio/music/ambient_music.wav");
	int sound = audio_manager->loadSound("audio/sfx/cold_space.wav");

	audio_manager->playMusic(music);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer); // initialize backbuffer
	is_running = true; // everything was set up successfully

	SDL_ShowWindow(window);
	SDL_RenderFillRect(renderer, NULL);

	auto asteroid1 = universe->spawnActor<Asteroid>({ { -500.f, -200.f }, { 100.f, 100.f }, 0.f, 50.f, "Asteroid_1" });
	auto asteroid2 = universe->spawnActor<Asteroid>({ {-100.0, 300.0}, {-50.f, -100.f}, 0.f, 30.f , "Asteroid_2" });
	auto asteroid3 = universe->spawnActor<Asteroid>({ {100.0, 300.0}, {0.5f, -30.f}, 0.f, 60.f , "Asteroid_3" });
	auto asteroid4 = universe->spawnActor<Asteroid>({ {-100.0, -300.0}, {0.5f, 200.f}, 0.f, 60.f , "Asteroid_3" });

	auto spaceship = universe->spawnActor<SpaceShip>({ { 0.f, 0.f }, { 0.f, 0.f }, 0.f, 0.f, "Ship" });

	universe->beginPlay();

	audio_manager->playMusic(0);
	audio_manager->playSound(0);

	while (is_running) {
		handleEvents();
		update();

		if (render() == RENDER_RESULT::RENDER_FAILED) {
			is_running = false;
			break;
		}
	}

	universe->endPlay();

	// frees memory associated with renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	audio_manager.reset();
	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

// Do physics
void update()
{
	universe->tick();
}

void renderActors()
{
	auto& actors = universe->getActors();
	ActorIdMap::iterator it = actors.begin();

	while (it != actors.end()) {
		auto& actor = it->second;

		if (!actor) {
			continue;
		}

		for (const auto& line : actor->getLines()) {
			renderLine(
				WINDOW_SIZE_HALF_F + actor->getPosition() + *actor->getVertexById(line.first),
				WINDOW_SIZE_HALF_F + actor->getPosition() + *actor->getVertexById(line.second),
				RGB{ 220, 220, 220 }
			);
		}

		it++;
	}
}

// Render the Game
int render()
{
	if (!is_active) RENDER_RESULT::RENDER_SUCCESS;

	SDL_SetRenderDrawColor(renderer, 26, 26, 32, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);

	renderActors();

	SDL_RenderPresent(renderer);

	return RENDER_RESULT::RENDER_SUCCESS;
}

// handles any events that SDL noticed.
void handleEvents()
{
	//the only event we'll check is the  SDL_QUIT event.
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				is_running = false;
			}
			break;
		}
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_FOCUS_LOST:

				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_RESTORED:
			case SDL_WINDOWEVENT_SHOWN:
				//case SDL_WINDOWEVENT_EXPOSED:
				is_active = true;
				break;
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
				is_active = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}