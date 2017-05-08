// Foward declarations

class bumper;

#if !defined(__forward__) && !defined(__nobb__elements__bumper__h)
#define __nobb__elements__bumper__h

// Libraries

#include <cmath>

// Includes

#include "geometry/vec.h"

class bumper
{
  // Members

  vec _position;
  double _radius;

public:

  // Constructors

  bumper(const vec &, const double &);

private:

  // Private constructors

  bumper();

public:

  // Getters

  const vec & position() const;
  const double & radius() const;
};

#endif
