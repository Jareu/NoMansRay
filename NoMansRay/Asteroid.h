#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
private:
	static constexpr uint16_t NUM_VERTICES = 12;
	static constexpr uint16_t MIN_RADIUS = 50;
	static constexpr uint16_t MAX_RADIUS = 150;
	void generate();
public:
	Asteroid() = delete;
	Asteroid(Universe& universe);
	~Asteroid() = default;
	void initialize(const SpawnParameters& spawn_parameters) override;
};