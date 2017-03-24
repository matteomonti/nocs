// Foward declarations

class atom;
class molecule;

#if !defined(__forward__) && !defined(__nobb__molecule__h)
#define __nobb__molecule__h

// Libraries

#include <iostream>
#include <cmath>
#include <vector>

#include "geometry/vec.h"

/* ATOM */

/*nota: vogliamo che un atomo NON sia modificabile una volta istanziato*/
/*se non nella posizione...*/

class atom
{
	// Memebers

	vec position;
	double radius;
	double mass;

public:

	// Constructors

	atom();
	atom(vec, double, double);

	// Public Methods

	vec getPosition() const;
	double getRadius() const;
	double getMass() const;

	void move(vec);
	void move(double x, double y);
};

// Standard Output

std :: ostream & operator << (std :: ostream &, const atom &);

/* MOLECULE */

class molecule
{
	// Members

	size_t size;
	atom * atoms;

	double mass;
	double angular_mass;

	vec position;
	vec velocity;
	double orientation;
	double angular_velocity;

	double time;
	unsigned int version;

public:

	// Constructors

	molecule();
	molecule(std :: vector<atom>, vec, vec, double, double);
	molecule(std :: vector<atom>);
	molecule(const molecule &);
	~molecule();

	// Public Methods

	size_t getSize() const;
	atom getAtom(unsigned int) const;
	double getMass() const;
	double getAngular_mass() const;
	vec getPosition() const;
	vec getVelocity() const;
	double getOrientation() const;
	double getAngular_velocity() const;
	double getTime() const;
	unsigned int getVersion() const;

private:

	// Private Methods

	vec getcdm();
	void correctposition();
};

// Standard Output

std :: ostream & operator << (std :: ostream &, const molecule &);

#endif
