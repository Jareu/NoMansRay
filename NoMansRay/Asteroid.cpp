#include "Asteroid.h"
#include "maths.h"
#include <cstdlib>
#include <cmath>
#include <vector>

Asteroid::Asteroid(Universe& universe) :
	Actor(universe)
{}

// Generate 
void Asteroid::generate()
{
	std::vector<int> angle_slices{};
	int slice_total = 0;
	std::vector<int> radii{};

	for (uint16_t i = 0; i < NUM_VERTICES; i++) {
		radii.push_back(maths::random_range(MIN_RADIUS, MAX_RADIUS));
		auto slice = maths::random_range(0, 100);
		slice_total += slice;
		angle_slices.push_back(slice);
		lines_.push_back(std::make_pair(
			(i == 0 ? NUM_VERTICES - 1 : i - 1), i
		));
	}

	double angle = 0.0;

	for (uint16_t i = 0; i < NUM_VERTICES; i++) {
		angle += (2 * M_PI * angle_slices[i]) / slice_total;
		vertices_.push_back(Vector2<decimal>{
			static_cast<decimal>(radii[i] * std::cos(angle)),
			static_cast<decimal>(radii[i] * std::sin(angle))
		});
	}

	triangulate();
}

void Asteroid::triangulate()
{

}

void Asteroid::initialize(const SpawnParameters& spawn_parameters)
{
	generate();
}