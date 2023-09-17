#include "Actor.h"
#include "maths.h"
#include "globals.h"
#include <iostream>
#include "Universe.h"

Actor::Actor(Universe& universe) :
	Object(universe),
	vertices_{ VertexVector{} },
	lines_{ LineVector{} },
	graphic_type_{ eGraphicType::VECTOR },
	vertex_transforms_valid_{ false },
	physics_body_def_{},
	physics_body_{},
	physics_shape_{},
	density_{0.f},
	friction_{0.f},
	restitution_{0.f}
{}

void Actor::initializePhysics(b2BodyType bodyType)
{
	initializePhysics(bodyType, density_, friction_, restitution_);
}

void Actor::initializePhysics(b2BodyType bodyType, decimal density, decimal friction, decimal restitution)
{
	physics_body_def_ = std::make_unique<b2BodyDef>();
	physics_body_def_->type = bodyType;
	physics_body_def_->position.Set(position_.x(), position_.y());
	physics_body_def_->angle = rotation_radians_;

	density_ = density;
	friction_ = friction;
	restitution_ = restitution;

	physics_body_ = std::unique_ptr<b2Body>(universe_.getPhysics()->CreateBody(physics_body_def_.get()));

	physics_shape_ = std::make_unique<b2PolygonShape>();

	if (lines_.empty() || vertices_.empty()) {
		std::cout << "no shape from which to create physics." << std::endl;
		return;
	}
	
	b2Hull poly_hull;
	for (int line = 0; line<8; line++) {
		// TODO: check that the vertex exists
		auto vertex = vertices_[lines_[line].first];
		poly_hull.points[line] = { vertex.x(), vertex.y() };
	}

	physics_shape_->Set(poly_hull);
	physics_fixture_def_ = std::make_unique<b2FixtureDef>();
	physics_fixture_def_->shape = physics_shape_.get();
	physics_fixture_def_->density = density_;
	physics_fixture_def_->friction = friction_;
	physics_fixture_def_->restitution = restitution_;

	physics_body_->CreateFixture( physics_shape_.get(), 0.0f);
}

void Actor::updatePhysics()
{
	b2Vec2 position = physics_body_->GetPosition();
	setPosition({ position.x, position.y });
	setRotation(physics_body_->GetAngle());
}

void Actor::addVertex(const Vector2<decimal>& coordinates)
{
	vertices_.push_back(coordinates);
}

void Actor::addLine(uint32_t vertex_0, uint32_t vertex_1)
{
	lines_.push_back(std::make_pair(vertex_0, vertex_1));
}

const LineVector& Actor::getLines() const
{
	return lines_;
}

const VertexVector& Actor::getVertices()
{
	if (!vertex_transforms_valid_) {
		updateVertexTransforms();
	}
	return vertices_transformed_;
}

// TODO: implement optionals in case vertex vector is empty
const Vector2<decimal>& Actor::getVertexById(uint32_t vertex_id)
{
	if (!vertex_transforms_valid_) {
		updateVertexTransforms();
	}
	if (vertex_id >= vertices_transformed_.size()) {
		return Vector2<decimal>{};
	}
	return vertices_transformed_[vertex_id];
}

eGraphicType Actor::getGraphicType() const
{
	return graphic_type_;
}

void Actor::updateVertexTransforms()
{
	vertices_transformed_.clear();
	for (const auto& vertex : vertices_){
		vertices_transformed_.emplace_back(
			maths::rotate(vertex, rotation_radians_)
		);
	}

	vertex_transforms_valid_ = true;
}

void Actor::setRotation(const decimal& new_rotation)
{
	if (rotation_radians_ != new_rotation) {
		rotation_radians_ = new_rotation;
		vertex_transforms_valid_ = false;
	}
}
