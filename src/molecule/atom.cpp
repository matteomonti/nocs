#include "atom.h"

// Constructors

atom :: atom()
{
}

atom :: atom(const vec & position, const double & radius, const double & mass) : _position(position), _radius(radius), _mass(mass)
{
}

// Getters

const vec & atom :: position() const
{
	return this->_position;
}

const double & atom :: radius() const
{
	return this->_radius;
}

const double & atom :: mass() const
{
	return this->_mass;
}

void atom :: move(const vec & v)
{
	this->_position = v;
}

// Public Methods

// Standard Output

std :: ostream & operator << (std :: ostream & out, const atom & a)
{
	return out << "Position:\t(" << a.position().x << ", " << a.position().y << ")" << std :: endl
			   << "Radius:\t" << a.radius() << std :: endl
			   << "Mass:\t" << a.mass() << std :: endl;
}
