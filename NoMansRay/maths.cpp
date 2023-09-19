#include "maths.h"
#include <cmath>

Vector2<decimal> maths::rotate(const Vector2<decimal>& vertex, decimal angle_radians) {
	return Vector2<decimal>{
		vertex.x()* std::cos(angle_radians) - vertex.y() * std::sin(angle_radians),
		vertex.x()* std::sin(angle_radians) + vertex.y() * std::cos(angle_radians)
	};
}

int maths::random_range(int min, int max)
{
	return min + (std::rand() % (max - min + 1));
}

decimal maths::get_distance_between_two_points(const Vector2<decimal>& point1, const Vector2<decimal>& point2)
{
	decimal dx = point2.x() - point1.x();
	decimal dy = point2.y() - point1.y();

	return sqrt(dx * dx + dy * dy);
}

bool maths::vertex_is_in_circumcenter(const Triangle& triangle, const Vector2<decimal>& vertex_to_test)
{
	const auto center_radius_pair = maths::get_circumcenter(triangle);
	const auto& center = center_radius_pair.first;
	auto radius = center_radius_pair.second;
	float distance = sqrt((center.x() - vertex_to_test.x()) * (center.x() - vertex_to_test.x()) + (center.y() - vertex_to_test.y()) * (center.y() - vertex_to_test.y()));
	bool in_circumcenter = (distance < radius);
	return in_circumcenter;
}