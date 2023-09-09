#include "Thruster.h"

Thruster::Thruster(Universe& universe, float max_thrust) :
	Actor(universe),
	throttle_{0.f},
	MAX_THRUST{ max_thrust }
{}

void Thruster::setThrottle(float throttle)
{
	throttle_ = throttle;
}

float Thruster::getThrottle()
{
	return throttle_;
}