#pragma once
#include "globals.h"
#include <vector>
#include <array>

class Triangle {
private:
	uint32_t id_;
	const VertexVector* vertices_;
	std::array<uint32_t, 3> vertex_indices_ = { 0, 0, 0 };
	std::array<std::pair<uint32_t, uint32_t>, 3> edges_;
public:
	Triangle() = delete;
	Triangle(const VertexVector* vertices);
	Triangle(const VertexVector* vertices, uint32_t id);
	Triangle(const VertexVector* vertices, uint32_t id, uint32_t v1, uint32_t v2, uint32_t v3);
	~Triangle() = default;
	Triangle(const Triangle& other_triangle);

	// Id
	uint32_t getId() const;
	void setId(uint32_t new_id);

	// Vertices
	void setVertices(uint32_t v1, uint32_t v2, uint32_t v3);
	std::array<uint32_t, 3> getVertices() const;
	Vector2<decimal> getV1() const;
	Vector2<decimal> getV2() const;
	Vector2<decimal> getV3() const;
	Vector2<decimal> getVertexById(uint8_t vertex_id) const;
	bool hasVertex(uint32_t vertex_id);

	// Edges
	std::array<std::pair<uint32_t, uint32_t>, 3> getEdges() const;
	std::pair<uint32_t, uint32_t> getEdge1() const;
	std::pair<uint32_t, uint32_t> getEdge2() const;
	std::pair<uint32_t, uint32_t> getEdge3() const;
	std::pair<uint32_t, uint32_t> getEdgeById(uint8_t edge_id) const;
	bool hasEdge(const std::pair<uint32_t, uint32_t>& edge);
};
