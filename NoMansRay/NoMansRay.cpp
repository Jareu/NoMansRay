// NoMansRay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(push, 0)
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
#include "Asteroid.h"

int		main();
void	handleEvents();
void	update();
int		render();

auto universe = std::make_unique<Universe>(1234);
b2Vec2 gravity_{ 0.0f, 9.814f };
b2World physics = b2World(gravity_);

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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		// SDL failed. Output error message and exit
		std::cout << "Failed to initialize SDL:" << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

	// Create Window
	window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FLAGS);
	if (!window) {
		std::cout << "Failed to create window: " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

	// set window size
	SDL_SetWindowMinimumSize(window, 100, 100);
	SDL_GetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

	// Create Renderer
	renderer = SDL_CreateRenderer(window, SDL_WINDOW_INDEX, SDL_RENDERER_FLAGS);
	if (!renderer) {
		std::cout << "Failed to create renderer: " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer); // initialize backbuffer
	is_running = true; // everything was set up successfully

	SDL_ShowWindow(window);
	SDL_RenderFillRect(renderer, NULL);

	auto asteroid1 = universe->spawnActor<Asteroid>();
	auto asteroid2 = universe->spawnActor<Asteroid>();
	auto asteroid3 = universe->spawnActor<Asteroid>();

	asteroid1->setLinearVelocity(Vector2<decimal>(0.4f, 0.2f));
	asteroid1->setAngularVelocity(-0.1f);

	asteroid2->setLinearVelocity(Vector2<decimal>(0.1f, 0.2f));
	asteroid2->setAngularVelocity(0.15f);
	asteroid2->setPosition(Vector2<decimal>{-300.0, 300.0});

	asteroid3->setLinearVelocity(Vector2<decimal>(0.5f, -0.4f));
	asteroid3->setAngularVelocity(0.2f);
	asteroid3->setPosition(Vector2<decimal>{300.0, 300.0});


	// Ground box
	float ground_box_height_half = 10.f;

	SpawnParameters ground_params{
		Vector2<decimal> {ZERO_DECIMAL, WINDOW_HEIGHT_HALF_F - ground_box_height_half - 1.f},
		Vector2<decimal> {ZERO_DECIMAL, ZERO_DECIMAL},
		ZERO_DECIMAL,
		ZERO_DECIMAL
	};

	auto ground_box = universe->spawnActor(ground_params);
	ground_box->addVertex({ -WINDOW_WIDTH_HALF_F + 1.f, -ground_box_height_half });
	ground_box->addVertex({ WINDOW_WIDTH_HALF_F - 1.f, -ground_box_height_half });
	ground_box->addVertex({ WINDOW_WIDTH_HALF_F - 1.f, ground_box_height_half });
	ground_box->addVertex({ -WINDOW_WIDTH_HALF_F + 1.f, ground_box_height_half });
	ground_box->addLine(0, 1);
	ground_box->addLine(1, 2);
	ground_box->addLine(2, 3);
	ground_box->addLine(3, 0);

	b2BodyDef* ground_body_def_ = new b2BodyDef();
	ground_body_def_->position.Set(ground_params.position.x(), ground_params.position.y());

	auto groundBody = physics.CreateBody(ground_body_def_);

	auto groundBox = new b2PolygonShape();
	groundBox->SetAsBox(WINDOW_WIDTH_HALF_F, ground_box_height_half);
	groundBody->CreateFixture(groundBox, 0.0f);

	// Dynamic Box

	float box_size_half = 30.f;
	auto box = universe->spawnActor();
	box->addVertex({ -box_size_half, -box_size_half });
	box->addVertex({ -box_size_half, box_size_half });
	box->addVertex({ box_size_half, box_size_half });
	box->addVertex({ box_size_half, -box_size_half });
	box->addLine(0, 1);
	box->addLine(1, 2);
	box->addLine(2, 3);
	box->addLine(3, 0);

	b2BodyDef* box_body_def_ = new b2BodyDef();
	box_body_def_->type = b2_dynamicBody;
	box_body_def_->position.Set(0.f, 0.f);
	box_body_def_->angle = M_PI_4 / 6;
	auto box_body = physics.CreateBody(box_body_def_);

	auto dynamicBox = new b2PolygonShape();
	dynamicBox->SetAsBox(box_size_half, box_size_half);

	auto fixtureDef = new b2FixtureDef();
	fixtureDef->shape = dynamicBox;
	fixtureDef->density = 1.0f;
	fixtureDef->friction = 0.3f;
	fixtureDef->restitution = 0.5f;

	box_body->CreateFixture(fixtureDef);

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	float timestep = 1.f / 500.f;

	while (is_running) {
		handleEvents();
		update();

		physics.Step(timestep, velocityIterations, positionIterations);
		b2Vec2 position = box_body->GetPosition();
		float angle = box_body->GetAngle();
		box->setPosition({ position.x, position.y });
		box->setRotation({ angle });

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

	IMG_Quit();
	SDL_Quit();

	return 0;
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
				WINDOW_SIZE_HALF_F + actor->getPosition() + actor->getVertexById(line.first),
				WINDOW_SIZE_HALF_F + actor->getPosition() + actor->getVertexById(line.second),
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