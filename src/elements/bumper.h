// Foward declarations

class bumper;

#if !defined(__forward__) && !defined(__nobb__elements__bumper__h)
#define __nobb__elements__bumper__h

// Libraries

#include <cmath>

// Includes

#include "geometry/vec.h"
#include "engine/grid.h"

class bumper
{
  // Members

  vec _position;
  double _radius;

public:

  // Constructors

  bumper();
  bumper(const vec &, const double &);

  // Public members

  grid :: mark mark;

  // Getters

  const vec & position() const;
  const double & radius() const;
};

#endif
