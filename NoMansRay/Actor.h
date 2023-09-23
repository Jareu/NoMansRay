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

public:
	Actor() = delete;
	Actor(Universe& universe);
	~Actor() = default;

	virtual void addVertex(const Vector2<decimal>& coordinates);
	virtual void addLine(uint32_t vertex_0, uint32_t vertex_1);
	void setRotation(const decimal& new_rotation) override;
	virtual const LineVector& getLines() const;
	virtual const VertexVector& getVertices();
	virtual const Vector2<decimal>* getVertexById(uint32_t vertex_id);
	eGraphicType getGraphicType() const;
	void initializePhysics(b2BodyType bodyType);
	void initializePhysics(b2BodyType bodyType, decimal density, decimal friction, decimal restitution);
	void updatePhysics(decimal seconds_elapsed);
	void updateVertexTransforms();
};