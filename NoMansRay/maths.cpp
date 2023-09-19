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

std::pair<Vector2<decimal>, decimal> maths::get_circumcenter(const Triangle& triangle)
{
	auto a = triangle.getV1();
	auto b = triangle.getV1();
	auto c = triangle.getV1();

	const decimal d = 2 * (a.x() * (b.y() - c.y()) + b.x() * (c.y() - a.y()) + c.x() * (a.y() - b.y()));

	decimal a2 = a.x() * a.x() + a.y() * a.y();
	decimal b2 = b.x() * b.x() + b.y() * b.y();
	decimal c2 = c.x() * c.x() + c.y() * c.y();

	decimal circumcenter_x = (a2 * (b.y() - c.y()) + b2 * (c.y() - a.y()) + c2 * (a.y() - b.y())) / d;
	decimal circumcenter_y = (a2 * (c.x() - b.x()) + b2 * (a.x() - c.x()) + c2 * (b.x() - a.x())) / d;

	decimal radius = sqrt((circumcenter_x - a.x()) * (circumcenter_x - a.x()) + (circumcenter_y - a.y()) * (circumcenter_y - a.y()));

	return std::make_pair(Vector2<decimal>(circumcenter_x, circumcenter_y), radius);
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