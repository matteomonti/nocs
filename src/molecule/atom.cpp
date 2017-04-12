#include "atom.h"

// printer

// Constructors

atom :: printer :: printer(std :: ostream & out) : _out(& out)
{
	(*(this->_out)) << std :: endl << std :: setw(16) << "position" << std :: setw(8) << "mass" << std :: setw(8) << "radius" <<  std :: endl;
}

// Operators

atom :: printer atom :: printer :: operator << (const atom & a)
{
	(*(this->_out)) << std :: setw(16) << a.position() << std :: setw(8) << a.mass() << std :: setw(8) << a.radius() << std :: endl;
	return *this;
}

template <typename type> std :: ostream & atom :: printer :: operator << (const type & x)
{
	return (*(this->_out)) << x;
}

// atom

// Constructors

atom :: atom(const vec & position, const double & mass, const double & radius) : _position(position), _mass(mass), _radius(radius)
{
}

// Private constructors

atom :: atom()
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

// Setters

atom & atom :: position(const vec & position)
{
	this->_position = position;
    return *this;
}

// Standard Output

atom :: printer operator << (std :: ostream & out, const atom & a)
{
	return atom :: printer(out) << a;
}
