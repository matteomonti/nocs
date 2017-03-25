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

// Public Methods

void atom :: move(const vec & v)
{
	this->_position = v;
}

// Public Nested Classes

// Constructors

atom :: printer :: printer()
{
}

atom :: printer :: printer(std :: ostream & out) : out(& out)
{
	(*(this->out)) << std :: endl << "-----CARATTERISTICHE ATOMI-----" << std :: endl << "m\tr\tq" << std :: endl;
}

// Operators

atom :: printer & atom :: printer :: operator << (const atom & a)
{
	(*(this->out)) << a.mass() << "\t" << a.radius() << "\t" << a.position() << std :: endl;
	return *this;
}

template <typename type> std :: ostream & atom :: printer :: operator << (const type & x)
{
	return (*(this->out)) << x;
}

// Standard Output

atom :: printer & operator << (std :: ostream & out, const atom & a)
{
	return atom :: printer(out) << a;
}
