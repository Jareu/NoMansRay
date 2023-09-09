#include "Actor.h"
#include "maths.h"

Actor::Actor(Universe& universe) :
	Object( universe ),
	vertices_{ VertexVector{} },
	lines_{ LineVector{} },
	graphic_type_{ eGraphicType::VECTOR },
	vertex_transforms_valid_{ false }
{ }

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
