#include "Thruster.h"
#include "utilities.h"

Thruster::Thruster(Universe& universe, float max_thrust) :
	Actor(universe),
	throttle_{0.f},
	MAX_THRUST{ max_thrust }
{
	update_thrust();
}

void Thruster::initialize()
{
	generate();
}

void Thruster::generate()
{
	utilities::add_vertex_to_vector(vertices_, -5.0f, -10.0f);
	utilities::add_vertex_to_vector(vertices_, 5.0f, -10.0f);
	utilities::add_vertex_to_vector(vertices_, 5.0f, 10.0f);
	utilities::add_vertex_to_vector(vertices_, -5.0f, 10.0f);

	utilities::generate_lines_from_vertices(lines_, vertices_);
}

void Thruster::update_thrust()
{
	thrust_ = 
	{
		std::cos(rotation_radians_) * throttle_ * MAX_THRUST,
		std::sin(rotation_radians_) * throttle_ * MAX_THRUST
	};
}

void Thruster::setThrottle(float throttle)
{
	throttle_ = throttle;
}

float Thruster::getThrottle()
{
	return throttle_;
}