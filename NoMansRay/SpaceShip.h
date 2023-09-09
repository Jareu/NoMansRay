#pragma once
#include "Actor.h"
#include "Thruster.h"

class SpaceShip : public Actor
{
protected:
	std::vector<Thruster> thrusters_{};
};