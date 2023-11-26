#include "utilities.h"

inline void utilities::add_vertex_to_vector(VertexVector& vertex_vector, decimal x, decimal y)
{
	vertex_vector.emplace_back(Vector2<decimal>{static_cast<decimal>(x), static_cast<decimal>(y)});
}

void utilities::generate_lines_from_vertices(LineVector& line_vector, VertexVector& vertex_vector)
{
	if (vertex_vector.size() < 1) {
		return;
	}

	for (int i = 0; i < vertex_vector.size() - 1; i++)
	{
		line_vector.emplace_back(std::make_pair(i, i + 1));
	}

	line_vector.emplace_back(std::make_pair(vertex_vector.size()-1, 0));
}