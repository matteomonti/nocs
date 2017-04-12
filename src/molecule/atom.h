// Foward declarations

class atom;

#if !defined(__forward__) && !defined(__nobb__molecule__atom__h)
#define __nobb__molecule__atom__h

// Libraries

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

// Forward includes

#define __forward__
#include "atom.h"
#undef __forward__

// Includes

#include "geometry/vec.h"

class atom
{
public:

    // Public Nested Classes

	class printer
	{
    // Friends

    friend atom :: printer operator << (std :: ostream &, const atom &);

		// Members

		std :: ostream * _out;

		// Constructors

		printer(std :: ostream &);

    public:

		// Operators

		printer operator << (const atom &);
		template <typename type> std :: ostream & operator << (const type &);
	};

private:

  // Friends

  friend class molecule;

	// Members

	vec _position;
  double _mass;
  double _radius;

public:

	// Constructors

  atom(const vec &, const double &, const double &);

private:

  // Private constructors

	atom();

public:

	// Getters

	const vec & position() const;
	const double & radius() const;
	const double & mass() const;

private:

  // Private setters

	atom & position(const vec &);
};

// Standard Output

atom :: printer operator << (std :: ostream &, const atom &);

#endif
