#pragma once
#include "types.h"

namespace maths {
	Vector2<decimal> rotate(const Vector2<decimal>& vertex, decimal angle_radians);
	int random_range(int min, int max);
	decimal get_distance_between_two_points(const Vector2<decimal>& point1, const Vector2<decimal>& point2);
	bool vertex_is_in_circumcenter(const Triangle& triangle, const Vector2<decimal>& vertex_to_test);
}

