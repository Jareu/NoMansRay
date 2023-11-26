#pragma once
#include "Actor.h"
#include "Thruster.h"

class SpaceShip : public Actor
{
private:
	void generate();
	void createPhysicsBody();
protected:
	std::vector<Thruster> thrusters_{};
public:
	SpaceShip() = delete;
	SpaceShip(Universe& universe);

	~SpaceShip() = default;

	void initialize(const SpawnParameters& spawn_parameters) override;
	void initialize() override;
	void beginPlay() override;
	void tick(decimal seconds_elapsed) override;
	void endPlay() override;
};