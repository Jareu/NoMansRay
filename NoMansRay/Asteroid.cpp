#include "Asteroid.h"
#include "maths.h"
#include "Delaunay.h"

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
	}

	double angle = 0.0;

	for (uint16_t i = 0; i < NUM_VERTICES; i++) {
		angle += (2 * M_PI * angle_slices[i]) / slice_total;
		vertices_.push_back(Vector2<decimal>{
			static_cast<decimal>(radii[i] * std::cos(angle)),
			static_cast<decimal>(radii[i] * std::sin(angle))
		});
		lines_.push_back(std::make_pair(
			(i == 0 ? NUM_VERTICES - 1 : i - 1), i
		));
	}

	triangulate();
}

void Asteroid::triangulate()
{
	Delaunay delaunay{ vertices_ };
	auto triangles = delaunay.processTriangulation();

	// Build list of unique edges
	// This builds up a concave hull
	/*
	LineVector new_lines{};
	for (int triangle_index = 0; triangle_index < triangles.size(); triangle_index++) {
		for (const auto& edge : triangles[triangle_index].getEdges()) {
			bool shared_edge = false;
			for (int other_triangle_index = 0; other_triangle_index < triangles.size(); other_triangle_index++) {
				if (triangle_index = other_triangle_index) {
					continue;
				}

				if (triangles[other_triangle_index].hasEdge(edge)) {
					shared_edge = true;
					break;
				}
			}

			if (shared_edge == false) {
				new_lines.push_back(edge);
			}
		}
	}
	*/

	// Add edges to line list if the aren't there already
	for (int triangle_index = 0; triangle_index < triangles.size(); triangle_index++) {
		for (const auto& edge : triangles[triangle_index].getEdges()) {
			bool line_exists = false;

			for (const auto& line : lines_) {
				if (line.first == edge.first && line.second == edge.second ||
					line.first == edge.second && edge.first == line.second)
				{
					line_exists = true;
					break;
				}
			}

			if (line_exists == false) {
				lines_.push_back(edge);
			}
		}
	}
}

void Asteroid::initialize(const SpawnParameters& spawn_parameters)
{
	generate();
}