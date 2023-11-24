#pragma once
#include <vector>
#include <memory>
#include <box2d.h>
#include "types.h"
#include "Object.h"

class Actor : public Object
{
protected:
	VertexVector vertices_;
	VertexVector vertices_transformed_;
	LineVector lines_;
	eGraphicType graphic_type_;
	bool vertex_transforms_valid_;

	b2BodyDef physics_body_def_;
	b2Body* physics_body_;
	b2PolygonShape physics_shape_;
	b2FixtureDef physics_fixture_def_;
	decimal density_;
	decimal friction_;
	decimal restitution_;
	Vector2<decimal> position_;
	Vector2<decimal> linear_velocity_;
	decimal rotation_radians_;
	decimal angular_velocity_;
	Vector2<decimal> scale_;
	bool transform_changed_;

	virtual void updateVertexTransforms();
public:
	Actor() = delete;
	Actor(Universe& universe);
	~Actor() = default;

	virtual void initialize(const SpawnParameters& spawn_parameters);

	// Getters
	virtual const VertexVector& getVertices();
	virtual const Vector2<decimal>* getVertexById(uint32_t vertex_id);
	virtual eGraphicType getGraphicType() const;
	virtual const LineVector& getLines() const;

	virtual const Vector2<decimal>& getPosition() const;
	virtual const Vector2<decimal>& getLinearVelocity() const;
	virtual const decimal& getRotation() const;
	virtual const decimal& getAngularVelocity() const;

	// Setters
	virtual void setPosition(const Vector2<decimal>& new_position);
	virtual void setPosition(decimal x, decimal y);
	virtual void setLinearVelocity(const Vector2<decimal>& new_linear_velocity);
	virtual void setLinearVelocity(decimal x, decimal y);
	virtual void setRotation(const decimal& new_rotation);
	virtual void setAngularVelocity(const decimal& new_angular_velocity);

	// Modifiers
	virtual void addVertex(const Vector2<decimal>& coordinates);
	virtual void addLine(uint32_t vertex_0, uint32_t vertex_1);

	// Physics
	virtual void initializePhysics();
	virtual void initializePhysics(b2BodyType bodyType);
	virtual void initializePhysics(b2BodyType bodyType, decimal density, decimal friction, decimal restitution);
	virtual void updatePhysics(decimal seconds_elapsed);
};