#include "bumper.h"

// Constructors

bumper :: bumper()
{
}

bumper :: bumper(const vec & position, const double & radius) : _position(position), _radius(radius)
{
}

// Getters

const vec & bumper :: position() const
{
  return this->_position;
}

const double & bumper :: radius() const
{
  return this->_radius;
}
