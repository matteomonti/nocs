// Foward declarations

class molecule;

#if !defined(__forward__) && !defined(__nobb__molecule__h)
#define __nobb__molecule__molecule__h

// Libraries

#include <iostream>
#include <cmath>
#include <vector>

// Includes

#include "geometry/vec.h"
#include "molecule/atom.h"

class molecule
{
	// Members

	size_t _size;
	atom * _atoms;

	double _mass;
	double _inertia_moment;

	vec _position;
	vec _velocity;

	double _orientation;
	double _angular_velocity;

	double _time;
	unsigned int _version;

public:

	// Constructors

	molecule();
	molecule(const std :: vector<atom> &, const vec & = vec(0, 0), const vec & = vec(0, 0), const double & = 0, const double & = 0);
	molecule(const molecule &);

	// Destructor

	~molecule();

	// Getters

	const size_t & size() const;
	const atom & atoms(const size_t &) const;
	const double & mass() const;
	const double & inertia_moment() const;
	const vec & position() const;
	const vec & velocity() const;
	const double & orientation() const;
	const double & angular_velocity() const;
	const double & time() const;
	const unsigned int & version() const;

};

// Standard Output

std :: ostream & operator << (std :: ostream &, const molecule &);

#endif
