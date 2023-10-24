#include "Object.h"

Object::Object(Universe& universe) : 
	universe_{ universe }
{ }

void Object::beginPlay()
{

}

void Object::tick(decimal seconds_elapsed)
{

}

void Object::endPlay()
{

}

void Object::initialize(const std::string& name)
{
	name_ = name;
}

void Object::initialize()
{ }

void Object::setName(const std::string& name)
{
	name_ = name;
}

const std::string Object::getName()
{
	return name_;
}