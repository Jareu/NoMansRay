#pragma once
#include "types.h"
#include <string>

class Universe;

class Object
{
protected:
	Universe& universe_;
	std::string name_;
public:
	Object() = delete;
	Object(Universe& universe);
	~Object() = default;

	virtual void beginPlay();
	virtual void tick(decimal seconds_elapsed);
	virtual void endPlay();
	virtual void initialize(const std::string& spawn_parameters);
	virtual void initialize();

	// Setters
	virtual void setName(const std::string& name);

	// Getters
	virtual const std::string getName();
};