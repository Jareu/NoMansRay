#pragma once

#include "globals.h"
#include "Triangle.h"
#include <set>

class Delaunay
{
private:
	VertexVector* vertices_;
	std::vector<Triangle> triangles_;
	Triangle super_triangle_;
	LineVector hull_;
	bool triangulation_valid_;

	void addVertex(uint32_t vertex_id);
	void createSuperTriangle();
	std::tuple<decimal, decimal, decimal, decimal> findRectangleAroundPoints();
	void removeTriangles(const std::set<uint32_t>& triangles_to_delete);
	void finish();
	LineVector buildEdgesAroundPoint(const std::set<uint32_t>& bad_triangles);
	void FindHullEdges(const Triangle& triangle, std::vector<std::pair<Line, bool>>& bad_triangle_edges);
public:
	Delaunay() = delete;
	Delaunay(VertexVector* vertices_);
	~Delaunay() = default;
	std::vector<Triangle>& getTriangulation();
	LineVector& getConcaveHull();
};