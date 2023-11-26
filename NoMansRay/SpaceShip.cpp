#include "SpaceShip.h"
#include "utilities.h"
#include "Universe.h"
#include "maths.h"

SpaceShip::SpaceShip(Universe& universe) : Actor(universe)
{
	thrusters_.push_back(Thruster{universe_, 20'000.f });
}

void SpaceShip::initialize()
{
	generate();
	createPhysicsBody();

	for (auto& thruster : thrusters_)
	{
		thruster.setThrottle(1.0f);
		thruster.setPosition({ 0.0f, 20.f }); // thruster offset
		thruster.setRotation(-M_PI_2); // thruster offset
	}
}

void SpaceShip::generate()
{
	utilities::add_vertex_to_vector(vertices_, 0.0f, -30.0f);
	utilities::add_vertex_to_vector(vertices_, 20.0f, 20.0f);
	utilities::add_vertex_to_vector(vertices_, -20.0f, 20.0f);

	utilities::generate_lines_from_vertices(lines_, vertices_);
}

void SpaceShip::createPhysicsBody()
{
	physics_body_def_.type = b2BodyType::b2_dynamicBody;
	physics_body_def_.position.Set(position_.x(), position_.y());
	physics_body_def_.angle = rotation_radians_;
	physics_body_def_.gravityScale = 0.f;

	density_ = 0.5f;
	friction_ = 0.1f;
	restitution_ = 0.8f;

	physics_body_ = universe_.getPhysics()->CreateBody(&physics_body_def_);

	// create physics bodies
	b2PolygonShape shape{};
	b2FixtureDef fixture_def{};

	b2Hull poly_hull;
	poly_hull.count = vertices_.size();

	for (int v = 0; v < vertices_.size(); v++) {
		poly_hull.points[v] = { vertices_.at(v).x(), vertices_.at(v).y() };
	}

	shape.Set(poly_hull);
	fixture_def.shape = &shape;
	fixture_def.density = density_;
	fixture_def.friction = friction_;
	fixture_def.restitution = restitution_;
	physics_body_->CreateFixture(&fixture_def);
}

void SpaceShip::beginPlay()
{

}

void SpaceShip::tick(decimal seconds_elapsed)
{
	if (!physics_body_) {
		return;
	}

	for (const auto& thruster : thrusters_)
	{
		auto thrust = maths::rotate(thruster.getThrust(), rotation_radians_);
		auto thruster_position = maths::rotate(thruster.getPosition(), rotation_radians_);
		physics_body_->ApplyForce({ thrust.x(), thrust.y() }, { thruster_position.x(), thruster_position.y() }, true);
	}	
}

void SpaceShip::endPlay()
{

}
