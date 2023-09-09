#pragma once
#include <vector>
#include "types.h"
#include "Object.h"

typedef std::vector<std::pair<uint32_t, uint32_t>> LineVector;
typedef std::vector<Vector2<decimal>> VertexVector;

class Actor : public Object
{
protected:
	VertexVector vertices_;
	VertexVector vertices_transformed_;
	LineVector lines_;
	eGraphicType graphic_type_;
	bool vertex_transforms_valid_;

public:
	Actor() = delete;
	Actor(Universe& universe);
	~Actor() = default;

	virtual void addVertex(const Vector2<decimal>& coordinates);
	virtual void addLine(uint32_t vertex_0, uint32_t vertex_1);
	void setRotation(const decimal& new_rotation) override;
	virtual const LineVector& getLines() const;
	virtual const VertexVector& getVertices();
	virtual const Vector2<decimal>& getVertexById(uint32_t vertex_id);
	eGraphicType getGraphicType() const;
	
	void updateVertexTransforms();
};