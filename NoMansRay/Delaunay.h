#pragma once

#include "globals.h"
#include "types.h"
#include "Triangle.h"
#include <set>

class Delaunay
{
private:
	const std::vector<Vector2<decimal>>& vertices_;
	std::vector<Triangle> triangles_{};
	std::vector<Vector2<decimal>> super_triangle_vertices_ {};
	Triangle super_triangle_;

	void addVertex(uint32_t vertex_id);
	void createSuperTriangle();
	std::tuple<decimal, decimal, decimal, decimal> findRectangleAroundPoints();
	void removeTriangles(const std::set<uint32_t>& triangles_to_delete);
	void finish();
	std::vector<std::pair<uint32_t, uint32_t>> buildEdgesAroundPoint(const std::set<uint32_t>& bad_triangles);
	void findMinMaxXY();
public:
	Delaunay() = delete;
	Delaunay(const std::vector<Vector2<decimal>>& vertices_);
	~Delaunay() = default;
	std::vector<Triangle> processTriangulation();
};