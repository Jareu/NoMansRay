#include "Object.h"

Object::Object(Universe& universe) : 
	universe_{ universe },
	position_{},
	linear_velocity_{},
	rotation_radians_{ ZERO_DECIMAL },
	angular_velocity_{ ZERO_DECIMAL },
	scale_{ ONE_DECIMAL, ONE_DECIMAL },
	transform_changed_ { true }
{ }

void Object::beginPlay()
{

}

void Object::tick(const decimal seconds_elapsed)
{

}

void Object::endPlay()
{

}

void Object::initialize(const SpawnParameters& spawn_parameters)
{
	position_ = spawn_parameters.position;
	linear_velocity_ = spawn_parameters.linear_velocity;
	rotation_radians_ = spawn_parameters.rotation_radians;
	angular_velocity_ = spawn_parameters.angular_velocity;
}

// Setters
void Object::setPosition(const Vector2<decimal>& new_position)
{
	position_ = new_position;
}

void Object::setLinearVelocity(const Vector2<decimal>& new_linear_velocity)
{
	linear_velocity_ = new_linear_velocity;
}

void Object::setRotation(const decimal& new_rotation)
{
	rotation_radians_ = new_rotation;
}

void Object::setAngularVelocity(const decimal& new_angular_velocity)
{
	angular_velocity_ = new_angular_velocity;
}

// Getters
const Vector2<decimal>& Object::getPosition()
{
	return position_;
}

const Vector2<decimal>& Object::getLinearVelocity()
{
	return linear_velocity_;
}

const decimal& Object::getRotation()
{
	return rotation_radians_;
}

const decimal& Object::getAngularVelocity()
{
	return angular_velocity_;
}
