#pragma once
#include <unordered_map>
#include <chrono>
#include <random>

#include "Actor.h"
#include "types.h"

typedef uint32_t ActorId;
typedef std::unordered_map<ActorId, Actor*> ActorIdMap;

class Universe
{
private:
	ActorId last_id_;
	ActorIdMap actor_map_{};
	std::chrono::system_clock::time_point last_tick_time_;
	int RANDOM_SEED;
public:
	Universe() = delete;
	Universe(const int seed);
	~Universe() = default;

	template <class T = Actor>
	Actor* spawnActor(const SpawnParameters& spawn_parameters);

	template <class T = Actor>
	Actor* spawnActor();

	ActorIdMap& getActors();

	void tick();
	void updatePhysics();
	void endExistance();
};

#include "Universe.inl"