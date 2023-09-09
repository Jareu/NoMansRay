template <class T = Actor>
Actor* Universe::spawnActor(const SpawnParameters& spawn_parameters)
{
	static_assert(std::is_convertible<T*, Actor*>::value, "Derived must inherit Base as public");
	Actor* new_actor = static_cast<Actor*>(new T(*this));
	new_actor->initialize(spawn_parameters);
	last_id_++;
	actor_map_.emplace(last_id_, new_actor);
	new_actor->beginPlay();
	return new_actor;
}

template <class T = Actor>
Actor* Universe::spawnActor()
{
	auto default_parameters = SpawnParameters{
		Vector2<decimal> {ZERO_DECIMAL, ZERO_DECIMAL},
		Vector2<decimal> {ZERO_DECIMAL, ZERO_DECIMAL},
		ZERO_DECIMAL,
		ZERO_DECIMAL
	};

	return spawnActor<T>(default_parameters);
}