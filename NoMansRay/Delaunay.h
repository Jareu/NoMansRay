#pragma once

#include "globals.h"
#include "Triangle.h"
#include <set>

class Delaunay
{
private:
	VertexVector* vertices_;
	std::vector<Triangle> triangles_{};
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
	Delaunay(VertexVector* vertices_);
	~Delaunay() = default;
	std::vector<Triangle> processTriangulation();
};