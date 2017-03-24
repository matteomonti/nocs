// Foward declarations

class atom;

#if !defined(__forward__) && !defined(__nobb__molecule__h)
#define __nobb__molecule__atom__h

// Libraries

#include <iostream>
#include <cmath>
#include <vector>

#include "geometry/vec.h"

/*nota: vogliamo che un atomo NON sia modificabile una volta istanziato*/
/*se non nella posizione...*/

class atom
{
	// Memebers

	vec _position;
	double _radius;
	double _mass;

public:

	// Constructors

	atom();
	atom(const vec &, const double &, const double &);

	// Getters

	const vec & position() const;
	const double & radius() const;
	const double & mass() const;

  // Public Methods

	void move(const vec &);
};

// Standard Output

std :: ostream & operator << (std :: ostream &, const atom &);

#endif
