#pragma once
#include "globals.h"

namespace utilities {
	extern inline void add_vertex_to_vector(VertexVector& vertex_vector, decimal x, decimal y);
	extern void generate_lines_from_vertices(LineVector& line_vector, VertexVector& vertex_vector);
}
