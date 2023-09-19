#pragma once
#include "types.h"

namespace maths {
	Vector2<decimal> rotate(const Vector2<decimal>& vertex, decimal angle_radians);
	int random_range(int min, int max);
	bool vertex_is_in_circumcenter(const Triangle& triangle, const Vector2<decimal>& vertex_to_test);
}

