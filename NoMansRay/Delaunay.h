#pragma once

#include "globals.h"
#include "types.h"
#include "Triangle.h"
#include <set>

class Delaunay
{
private:
	const VertexVector& vertices_;
	std::vector<Triangle> triangles_{};
	VertexVector super_triangle_vertices_ {};
	Triangle super_triangle_;

	void addVertex(uint32_t vertex_id);
	void createSuperTriangle();
	std::tuple<decimal, decimal, decimal, decimal> findRectangleAroundPoints();
	void removeTriangles(const std::set<uint32_t>& triangles_to_delete);
	void finish();
	LineVector buildEdgesAroundPoint(const std::set<uint32_t>& bad_triangles);
	void findMinMaxXY();
public:
	Delaunay() = delete;
	Delaunay(const VertexVector& vertices_);
	~Delaunay() = default;
	std::vector<Triangle> processTriangulation();
};