// Foward declarations

class bumper;

#if !defined(__forward__) && !defined(__nobb__elements__bumper__h)
#define __nobb__elements__bumper__h

// Libraries

#include <cmath>
#include <assert.h>
#include <random>

// Includes

#include "geometry/vec.h"
#include "engine/grid.h"

class bumper
{
  // Members

  vec _position;
  double _radius;
  double _temperature;
  bool _multiplicative;
  bool _randomness;
  std :: exponential_distribution <double> _exp_distribution;
  std :: default_random_engine * _random_engine;
  

public:

  // Constructors

  bumper();
  bumper(const vec &, const double &, const double & = -1.0, const bool & = false, const bool & = false, std :: default_random_engine * = NULL);

  // Public members

  grid :: mark mark;

  // Getters

  const vec & position() const;
  const double & radius() const;
  const double & temperature() const;
  const bool & multiplicative() const;
  const bool & randomness() const;

  // Methods

  const double random_extraction();

};

#endif
