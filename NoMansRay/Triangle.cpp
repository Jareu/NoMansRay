#include "Triangle.h"
#include <iostream>

Triangle::Triangle(const std::vector<Vector2<decimal>>& vertices, uint32_t id) :
	id_{ id },
	vertices_{ vertices },
	vertex_indices_{ 0, 0, 0 },
	edges_{ std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0) }
{ }

Triangle::Triangle(const std::vector<Vector2<decimal>>& vertices, uint32_t id, uint32_t v1, uint32_t v2, uint32_t v3) :
	id_{ id },
	vertices_ { vertices },
	vertex_indices_{ v1, v2, v3 },
	edges_{ std::make_pair(v1, v2), std::make_pair(v2, v3), std::make_pair(v3, v1) }
{ }

Triangle::Triangle(const Triangle& other_triangle) :
	id_{ other_triangle.id_ },
	vertices_{ other_triangle.vertices_ },
	vertex_indices_{ other_triangle.vertex_indices_ },
	edges_{ other_triangle.edges_ }
{ }

Triangle& Triangle::operator=(const Triangle& rhs)
{
	return *this;
}

uint32_t Triangle::getId() const
{
	return id_;
}

void Triangle::setId(uint32_t new_id)
{
	id_ = new_id;
}

std::array<uint32_t, 3> Triangle::getVertices() const
{
	return vertex_indices_;
}

Vector2<decimal> Triangle::getV1() const
{
	return getVertexById(0);
}

Vector2<decimal> Triangle::getV2() const
{
	return getVertexById(1);
}

Vector2<decimal> Triangle::getV3() const
{
	return getVertexById(2);
}

void Triangle::setVertices(uint32_t v1, uint32_t v2, uint32_t v3)
{
	vertex_indices_[0] = v1;
	vertex_indices_[1] = v2;
	vertex_indices_[2] = v3;
	edges_[0] = std::make_pair(vertex_indices_[0], vertex_indices_[1]);
	edges_[1] = std::make_pair(vertex_indices_[1], vertex_indices_[2]);
	edges_[2] = std::make_pair(vertex_indices_[2], vertex_indices_[0]);
}

Vector2<decimal> Triangle::getVertexById(uint8_t vertex_id) const
{
	if (vertex_id > 2) {
		std::cout << "triangle vertex " << vertex_id << " outside of range for a triangle." << std::endl;
		return Vector2<decimal> {};
	}
	if (vertex_indices_[vertex_id] >= vertices_.size()) {
		std::cout << "triangle vertex " << vertex_id << " index " << vertex_indices_[vertex_id] << " doesn't exist in vertex list." << std::endl;
		return Vector2<decimal> {};
	}
	return vertices_[vertex_indices_[vertex_id]];
}

bool Triangle::hasVertex(uint32_t vertex_id)
{
	for (auto vertex_index : vertex_indices_) {
		if (vertex_id == vertex_index) {
			return true;
		}
	}
}

std::array<std::pair<uint32_t, uint32_t>, 3> Triangle::getEdges() const
{
	return edges_;
}

std::pair<uint32_t, uint32_t> Triangle::getEdge1() const
{
	return getEdgeById(0);
}

std::pair<uint32_t, uint32_t> Triangle::getEdge2() const
{
	return getEdgeById(1);
}

std::pair<uint32_t, uint32_t> Triangle::getEdge3() const
{
	return getEdgeById(2);
}

std::pair<uint32_t, uint32_t> Triangle::getEdgeById(uint8_t edge_id) const
{
	if (edge_id > 2) {
		std::cout << "triangle edge " << edge_id << " outside of range for a triangle." << std::endl;
		return std::pair<uint32_t, uint32_t> {0, 0};
	}
	return edges_[edge_id];
}

bool Triangle::hasEdge(const std::pair<uint32_t, uint32_t>& edge)
{
	for (const auto& my_edge : edges_) {
		if ((my_edge.second == edge.first && my_edge.first == edge.second) || 
			(my_edge.first == edge.first && my_edge.second == edge.second))
		{
			return true;
		}
	}
	
	return false;
}