#pragma once
#include "Actor.h"

class Thruster : Actor
{
private:
	float throttle_;

	void update_thrust();
	void generate();
public:
	const decimal MAX_THRUST;

	Thruster() = delete;
	Thruster(Universe& universe, float max_thrust);
	~Thruster() = default;

	void initialize() override;
	void setThrottle(decimal throttle);
	decimal getThrottle() const;
	Vector2<decimal> getThrust() const;
	virtual void setRotation(const decimal& new_rotation) override;
};