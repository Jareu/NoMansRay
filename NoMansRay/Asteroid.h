#pragma once
#include "Actor.h"
#include "Delaunay.h"

class Asteroid : public Actor
{
private:
	static constexpr uint16_t NUM_VERTICES = 12;
	static constexpr uint16_t MIN_RADIUS = 50;
	static constexpr uint16_t MAX_RADIUS = 150;
	std::unique_ptr<Delaunay> delaunay_;
	bool physics_is_setup_ = false;
	void generate();
	void triangulate();
	void addLinesFromTriangles(const std::vector<Triangle>& triangles);
public:
	Asteroid() = delete;
	Asteroid(Universe& universe);
	~Asteroid() = default;
	void initialize(const SpawnParameters& spawn_parameters) override;
	void initialize() override;
	void beginPlay() override;
	void tick(decimal seconds_elapsed) override;
	void endPlay() override;
	void updatePhysics(decimal seconds_elapsed) override;
};