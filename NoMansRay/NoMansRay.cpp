// NoMansRay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(push, 0)
#pragma warning( disable : 4468 )
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#pragma warning(pop)
#undef main

#include <stdlib.h>     /* srand, rand */
#include <iostream>

#include "globals.h"
#include "types.h"
#include "graphics.h"

#include <box2d.h>
#include "Universe.h"
#include "Asteroid.h"
#include "maths.h"

int		main();
void	handleEvents();
void	update();
int		render();

int loadMusic(const std::string& filename);
int loadSound(const std::string& filename);
void setVolume(uint32_t volume);

int playMusic(uint32_t music_index);
int playSound(uint32_t sound_index);

int initMixer();
void quitMixer();

void togglePlay();

auto universe = std::make_unique<Universe>(1234);
std::vector<Mix_Chunk*> sounds{};
std::vector<Mix_Music*> music{};

int loadMusic(const std::string& filename)
{
	Mix_Music* music_file = nullptr;
	music_file = Mix_LoadMUS(filename.c_str());
	if (music_file == nullptr) {
		std::cout << "Failed to load music. SDL_Mixer error: " << SDL_GetError() << std::endl;
		return -1;
	}
	music.emplace_back(music_file);
	return music.size() - 1;
}

int loadSound(const std::string& filename)
{
	Mix_Chunk* sound_file = nullptr;
	sound_file = Mix_LoadWAV(filename.c_str());
	if (sound_file == nullptr) {
		std::cout << "Failed to load sound. SDL_Mixer error: " << SDL_GetError() << std::endl;
		return -1;
	}
	sounds.emplace_back(sound_file);
	return sounds.size() - 1;
}

void setVolume(uint32_t volume)
{
	global_volume = (MIX_MAX_VOLUME * volume) / 100;
}

int playMusic(uint32_t music_index)
{
	if (music_index >= music.size() || Mix_PlayingMusic() != 0) {
		return 1;
	}

	Mix_Volume(1, global_volume);
	Mix_PlayMusic(music.at(music_index), -1);

	return 0;
}

int playSound(uint32_t sound_index)
{
	if (sound_index >= sounds.size()) {
		return 1;
	}

	Mix_Volume(-1, global_volume);
	Mix_PlayChannel(-1, sounds.at(sound_index), 0);

	return 0;
}

int initMixer()
{
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_Mixer could not initialize. Error: " << Mix_GetError() << std::endl;
		return -1;
	}
	setVolume(80);
	return 0;
}

void quitMixer()
{

	for (int s = 0; s < sounds.size(); s++) {
		Mix_FreeChunk(sounds.at(s));
		sounds.at(s) = nullptr;
	}
	for (int m = 0; m < music.size(); m++) {
		Mix_FreeMusic(music.at(m));
		music.at(m) = nullptr;
	}
	Mix_Quit();
}

void togglePlay()
{
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}

int main()
{
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

	initMixer();

	int music = loadMusic("audio/music/ambient_music.wav");
	int sound = loadSound("audio/sfx/cold_space.wav");

	playMusic(music);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer); // initialize backbuffer
	is_running = true; // everything was set up successfully

	SDL_ShowWindow(window);
	SDL_RenderFillRect(renderer, NULL);

	auto asteroid1 = universe->spawnActor<Asteroid>({ { 0.f, 0.f }, { 0.1f, 500.f }, 0.f, 50.f, "Asteroid_1" });
	auto asteroid2 = universe->spawnActor<Asteroid>({ {-100.0, 300.0}, {0.1f, 500.f}, 0.f, 30.f , "Asteroid_2" });
	auto asteroid3 = universe->spawnActor<Asteroid>({ {100.0, 300.0}, {0.5f, 500.f}, 0.f, 60.f , "Asteroid_3" });

	playMusic(0);
	playSound(0);

	while (is_running) {
		handleEvents();
		update();

		if (render() == RENDER_RESULT::RENDER_FAILED) {
			is_running = false;
			break;
		}
	}

	// frees memory associated with renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	quitMixer();
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