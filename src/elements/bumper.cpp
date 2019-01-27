#include "bumper.h"

// Constructors

bumper :: bumper()
{
}

bumper :: bumper(const vec & position, const double & radius, const double & temperature = -1.0) : _position(position), _radius(radius), _temperature(temperature)
{
  assert(this->_temperature == -1.0 || this->_temperature >= 0);
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

const double & bumper :: temperature() const
{
  return this->_temperature;
}
