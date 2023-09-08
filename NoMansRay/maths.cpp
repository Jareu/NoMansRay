#include "maths.h"
#include <cmath>

Vector2<decimal> maths::rotate(const Vector2<decimal>& vertex, decimal angle_radians) {
	return Vector2<decimal>{
		vertex.x()* std::cos(angle_radians) - vertex.y() * std::sin(angle_radians),
		vertex.x()* std::sin(angle_radians) + vertex.y() * std::cos(angle_radians)
	};
