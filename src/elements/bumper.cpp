#include "bumper.h"

// Constructors

bumper :: bumper(const vec & position, const double & radius) : _position(position), _radius(radius)
{}

// Private Constructors

bumper :: bumper()
{}

// Getters

const vec & bumper :: position() const
{
  return this->_position;
}

const double & bumper :: radius() const
{
  return this->_radius;
}
