#include "Delaunay.h"
#include "maths.h"
#include <algorithm>
#include <iostream>

Delaunay::Delaunay(VertexVector* vertices_) :
    vertices_ { vertices_ },
    super_triangle_ { vertices_, 0 }
{ }

std::vector<Triangle> Delaunay::processTriangulation()
{
    if (vertices_ == nullptr) {
        std::cout << "unable to process triangulation: vertex array is null" << std::endl;
        return std::vector<Triangle> {};
    }

    createSuperTriangle();

    for (int i = 0; i < vertices_->size(); i++) {
        addVertex(i);
    }

    finish();

    return triangles_;
}

void Delaunay::createSuperTriangle()
{
    constexpr float offset = 0.02;    

    auto rectangle = findRectangleAroundPoints();
    decimal origin_x = std::get<2>(rectangle);
    decimal origin_y = std::get<3>(rectangle);
    decimal rectangle_base = std::get<0>(rectangle);
    decimal rectangle_height = std::get<1>(rectangle);

    uint32_t id = vertices_->size();
    vertices_->emplace_back(Vector2<decimal>{ origin_x - rectangle_base - offset, origin_y - offset });
    vertices_->emplace_back(Vector2<decimal>{ origin_x + rectangle_base + offset, origin_y - offset });
    vertices_->emplace_back(Vector2<decimal>{ origin_x, origin_y + 2 * rectangle_height + offset });

    super_triangle_.setVertices(id, id + 1, id + 2);
    triangles_.push_back(super_triangle_);
}

std::tuple<decimal, decimal, decimal, decimal> Delaunay::findRectangleAroundPoints()
{
    decimal min_x_ = std::numeric_limits<decimal>::max();
    decimal min_y_ = std::numeric_limits<decimal>::max();
    decimal max_x_ = std::numeric_limits<decimal>::min();
    decimal max_y_ = std::numeric_limits<decimal>::min();

    for (const auto& vertex : *vertices_) {
        if (vertex.x() < min_x_) min_x_ = vertex.x();
        if (vertex.x() > max_x_) max_x_ = vertex.x();
        if (vertex.y() < min_y_) min_y_ = vertex.y();
        if (vertex.y() > max_y_) max_y_ = vertex.y();
    }

    decimal rect_base = max_x_ - min_x_;
    decimal rect_height = max_y_ - min_y_;
    decimal origin_x = min_x_ + rect_base / 2;
    decimal origin_y = min_y_;

    return { rect_base, rect_height, origin_x, origin_y };
}

void Delaunay::addVertex(uint32_t vertex_id)
{
    std::set<uint32_t> bad_triangles{};

    for (int i = 0; i < triangles_.size(); i++) {
        if(maths::vertex_is_in_circumcenter(triangles_.at(i), vertices_->at(vertex_id))) {
            bad_triangles.insert(i);
        }        
    }

    const auto edges_around_point = buildEdgesAroundPoint(bad_triangles);
    removeTriangles(bad_triangles);

    // retriangulate polygonal hole
    for (const auto& edge : edges_around_point) {
        Triangle new_triangle(vertices_, triangles_.size(), edge.first, edge.second, vertex_id);
        triangles_.push_back(new_triangle);
    }
}

void Delaunay::finish()
{
    std::set<uint32_t> bad_triangles{};

    // TODO: add edges connected to super triangle to convex hull list

    for (const auto& triangle : triangles_) {
        bool shares_vertex_with_super_triangle = false;

        for (const auto& vertex : triangle.getVertices()) {
            if (super_triangle_.hasVertex(vertex)) {
                shares_vertex_with_super_triangle = true;
                break;
            }
        }

        std::cout << "checking for concave triangles." << std::endl;
        bool is_concave = false;
        float cross_product = maths::cross_product(triangle.getV2() - triangle.getV1(), triangle.getV3() - triangle.getV2());
        if (cross_product < 0) {
            std::cout << "got concave triangle!" << std::endl;
        }

        if (shares_vertex_with_super_triangle || is_concave) {
            bad_triangles.insert(triangle.getId());
        }
    }

    removeTriangles(bad_triangles);

    // erase the vertices added for super triangle
    vertices_->erase(vertices_->end() - 3, vertices_->end());
}

LineVector Delaunay::buildEdgesAroundPoint(const std::set<uint32_t>& bad_triangles)
{
    LineVector edges_around_point{};

    for (const auto bad_triangle_index : bad_triangles) {
        // for each edge in triangle
        for (const auto& edge : triangles_.at(bad_triangle_index).getEdges()) {
            bool edge_shared = false;
            // if edge is not shared by any other triangles in bad triangles
            for (const auto other_bad_triangle_index : bad_triangles) {
                if (bad_triangle_index == other_bad_triangle_index) {
                    continue;
                }

                if (triangles_[other_bad_triangle_index].hasEdge(edge)) {
                    edge_shared = true;
                    break;
                }
            }

            if (!edge_shared) {
                edges_around_point.push_back(edge);
            }
        }
    }

    return edges_around_point;
}

void Delaunay::removeTriangles(const std::set<uint32_t>& triangles_to_delete)
{
    for (auto it = triangles_.begin(); it != triangles_.end();) {
        uint32_t id = it->getId();
        bool to_delete = triangles_to_delete.find(id) != triangles_to_delete.end();
        if (to_delete) {
            it = triangles_.erase(it);
        }
        else {
            it++;
        }
    }

    std::vector<int> test{ 0, 1, 2, 3, 4, 5, 6 };
    for (auto it = test.begin(); it != test.end();) {
        bool to_delete = triangles_to_delete.find(*it) != triangles_to_delete.end();
        if (to_delete) {
            it = test.erase(it);
        }
        else {
            it++;
        }
    }

    // refresh triangle IDs
    for (int index = 0; index < triangles_.size(); index++) {
        triangles_.at(index).setId(index);
    }
}

void Delaunay::getConcaveHull()
{
    // Build list of unique edges
    // This builds up a concave hull

    LineVector new_lines{};
    for (int triangle_index = 0; triangle_index < triangles.size(); triangle_index++) {
        for (const auto& edge : triangles[triangle_index].getEdges()) {
            bool shared_edge = false;
            for (int other_triangle_index = 0; other_triangle_index < triangles.size(); other_triangle_index++) {
                if (triangle_index = other_triangle_index) {
                    continue;
                }

                if (triangles[other_triangle_index].hasEdge(edge)) {
                    shared_edge = true;
                    break;
                }
            }

            if (shared_edge == false) {
                new_lines.push_back(edge);
            }
        }
    }

}