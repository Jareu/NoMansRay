#include "Asteroid.h"
#include "maths.h"
#include "Delaunay.h"
#include "Universe.h"

#include <cstdlib>
#include <cmath>
#include <vector>

Asteroid::Asteroid(Universe& universe) :
	Actor(universe)
{}

void Asteroid::tick(decimal seconds_elapsed)
{

}

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
	Delaunay delaunay{ &vertices_ };
	auto triangles = delaunay.processTriangulation();
	addLinesFromTriangles(triangles);

	physics_body_def_.type = b2BodyType::b2_dynamicBody;
	physics_body_def_.position.Set(position_.x(), position_.y());
	physics_body_def_.angle = rotation_radians_;
	physics_body_def_.gravityScale = 0.f;

	density_ = 1.f;
	friction_ = 0.1f;
	restitution_ = 0.8f;

	physics_body_ = universe_.getPhysics()->CreateBody(&physics_body_def_);

	// create physics bodies
	for (const auto& triangle : triangles) {
		b2PolygonShape shape{};
		b2FixtureDef fixture_def{};

		b2Hull poly_hull;
		poly_hull.count = 3;

		auto tri_verts = triangle.getVertices();
		for (int v = 0; v < tri_verts.size(); v++) {
			poly_hull.points[v] = { vertices_.at(tri_verts.at(v)).x(), vertices_.at(tri_verts.at(v)).y() };
		}

		shape.Set(poly_hull);
		fixture_def.shape = &shape;
		fixture_def.density = density_;
		fixture_def.friction = friction_;
		fixture_def.restitution = restitution_;
		physics_body_->CreateFixture(&fixture_def);
	}

	physics_body_->ApplyLinearImpulse({ physics_body_->GetMass() * linear_velocity_.x(), physics_body_->GetMass() * linear_velocity_.y() }, { position_.x(), position_.y() }, true);
	physics_body_->ApplyAngularImpulse(physics_body_->GetMass() * angular_velocity_, true);
}

void Asteroid::addLinesFromTriangles(const std::vector<Triangle>& triangles)
{
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
	Object::initialize(spawn_parameters);
	initialize();
}

void Asteroid::initialize()
{
	generate();
}