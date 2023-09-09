#pragma once
#include "Actor.h"

class Thruster : Actor
{
private:
	float throttle_;

public:
	const decimal MAX_THRUST;

	Thruster() = delete;
	Thruster(Universe& universe, float max_thrust);
	~Thruster() = default;

	void setThrottle(float throttle);
	float getThrottle();
};