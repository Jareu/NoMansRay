#include "Universe.h"
#include <algorithm>

Universe::Universe(const int seed) :
	last_id_{ 0 },
	actor_map_{},
	last_tick_time_{ std::chrono::system_clock::now() },
	RANDOM_SEED{ seed },
	physics_settings_{ 6, 2, {0.0f, 9.814f } },
	physics{ b2World(physics_settings_.gravity) }
{
	srand(RANDOM_SEED);
}

b2World* Universe::getPhysics()
{
	return &physics;
}

void Universe::tick()
{
	ActorIdMap::iterator it = actor_map_.begin();
	const auto now = std::chrono::system_clock::now();
	auto seconds_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - last_tick_time_).count() / static_cast<decimal>(1'000'000.0);

	physics.Step(seconds_elapsed, physics_settings_.velocity_iterations, physics_settings_.position_iterations);

	while (it != actor_map_.end()) {
		auto& object = it->second;

		if (object) {
			object->updatePhysics();
			object->tick(seconds_elapsed);

			object->setRotation(object->getRotation() + object->getAngularVelocity() * seconds_elapsed);
			object->setPosition(object->getPosition() + object->getLinearVelocity() * seconds_elapsed);
		}

		it++;
	}

	last_tick_time_ = now;
}

void Universe::endExistance()
{
	ActorIdMap::iterator it = actor_map_.begin();

	while (it != actor_map_.end()) {
		auto& actor = it->second;

		if (actor) {
			actor->endPlay();
			delete actor;
			actor_map_.erase(it->first);
		}

		it++;
	}
}

ActorIdMap& Universe::getActors()
{
	return actor_map_;
}