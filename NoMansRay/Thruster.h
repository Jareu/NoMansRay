#pragma once
#include "Actor.h"

class Thruster : public Actor
{
private:
	decimal throttle_;
	Vector2<decimal> thrust_;

	void update_thrust();
	void generate();
public:
	const decimal MAX_THRUST;

	Thruster() = delete;
	Thruster(Universe& universe, decimal max_thrust);
	~Thruster() = default;

	void setThrottle(decimal throttle);
	decimal getThrottle() const;
	Vector2<decimal> getThrust() const;
	virtual void setRotation(const decimal& new_rotation) override;
};