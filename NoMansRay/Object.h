#pragma once
#include "types.h"

class Universe;

class Object
{
protected:
	Universe& universe_;
	Vector2<decimal> position_;
	Vector2<decimal> linear_velocity_;
	decimal rotation_radians_;
	decimal angular_velocity_;
	Vector2<decimal> scale_;
	bool transform_changed_;
public:
	Object() = delete;
	Object(Universe& universe);
	~Object() = default;

	virtual void beginPlay();
	virtual void tick(const decimal seconds_elapsed);
	virtual void endPlay();
	virtual void initialize(const SpawnParameters& spawn_parameters);
	
	// Setters
	virtual void setPosition(const Vector2<decimal>& new_position);
	virtual void setPosition(decimal x, decimal y);
	virtual void setLinearVelocity(const Vector2<decimal>& new_linear_velocity);
	virtual void setLinearVelocity(decimal x, decimal y);
	virtual void setRotation(const decimal& new_rotation);
	virtual void setAngularVelocity(const decimal& new_angular_velocity);

	// Getters
	virtual const Vector2<decimal>& getPosition();
	virtual const Vector2<decimal>& getLinearVelocity();
	virtual const decimal& getRotation();
	virtual const decimal& getAngularVelocity();
};