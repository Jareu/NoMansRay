#include "Thruster.h"

Thruster::Thruster(Universe& universe, decimal max_thrust) :
	Actor(universe),
	throttle_{ 0.f },
	MAX_THRUST{ max_thrust }
{
	update_thrust();
}

void Thruster::update_thrust()
{
	thrust_ =
	{
		std::cos(rotation_radians_) * throttle_ * MAX_THRUST,
		std::sin(rotation_radians_) * throttle_ * MAX_THRUST
	};
}

void Thruster::setRotation(const decimal& new_rotation)
{
	Actor::setRotation(new_rotation);
	update_thrust();
}

void Thruster::setThrottle(decimal throttle)
{
	throttle_ = throttle;
	update_thrust();
}

decimal Thruster::getThrottle() const
{
	return throttle_;
}

Vector2<decimal> Thruster::getThrust() const
{
	return thrust_;
}