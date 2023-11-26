#pragma once
#include "Actor.h"
#include "Thruster.h"

class SpaceShip : public Actor
{
public:
	SpaceShip() = delete;
	SpaceShip(Universe& universe);

	~SpaceShip() = default;

	void initialize() override;
	void beginPlay() override;
	void tick(decimal seconds_elapsed) override;
	void endPlay() override;
protected:
	std::vector<Thruster> thrusters_{};
private:
	void generate();
	void createPhysicsBody();
};