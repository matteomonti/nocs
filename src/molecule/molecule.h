// Foward declarations

class molecule;

#if !defined(__forward__) && !defined(__nobb__molecule__molecule__h)
#define __nobb__molecule__molecule__h

// Libraries

#include <iostream>
#include <cmath>
#include <vector>

// Includes

#include "geometry/vec.h"
#include "molecule/atom.h"
#include "engine/grid.h"

class molecule
{
public:

  // Nested Classes

	class printer
	{
    // Friends

    friend molecule :: printer operator << (std :: ostream &, const molecule &);

		// Members

		std :: ostream * _out;

		// Constructors

		printer(std :: ostream &);

	public:
		// Operators

		printer operator << (const molecule &);
		template <typename type> std :: ostream & operator << (const type &);
	};

private:

	// Members

	size_t _size;
	atom * _atoms;

  vec _position;
  vec _velocity;

  double _orientation;
  double _angular_velocity;

	double _mass;
  double _radius;
	double _inertia_moment;

	double _time;
	unsigned int _version;

public:

  // Public members

  grid :: mark mark;

	// Constructors

	molecule();
	molecule(const std :: vector<atom> &, const vec & = vec(0, 0), const vec & = vec(0, 0), const double & = 0, const double & = 0);
	molecule(const molecule &);

	// Destructor

	~molecule();

	// Getters

	const size_t & size() const;
  const vec & position() const;
	const vec & velocity() const;
	const double & orientation() const;
	const double & angular_velocity() const;
	const double & radius() const;
	const double & mass() const;
	const double & inertia_moment() const;
	const double & time() const;
	const unsigned int & version() const;

	// Methods

  void integrate(const double &);
	void impulse(const vec &, const vec &);

	// Operators

	const atom & operator [] (const size_t &) const;
	molecule & operator ++ ();
	molecule operator ++ (int);
};

// Standard Output

molecule :: printer operator << (std :: ostream &, const molecule &);

#endif
