#ifndef __nobb__event__events__molecule_molecule__hpp
#define __nobb__event__events__molecule_molecule__hpp

#include "molecule_molecule.h"
#include "math/gss.hpp"
#include "math/secant.hpp"

namespace events
{
  // Static private methods

  inline vec molecule_molecule :: position(const molecule & molecule, const size_t & index, const int & fold)
  {
    return molecule.position() + vec(fold) + molecule[index].position() % molecule.orientation();
  }

  inline vec molecule_molecule :: position(const molecule & molecule, const size_t & index, const double & time, const int & fold)
  {
    double dt = time - molecule.time();
    return molecule.position() + vec(fold) + molecule.velocity() * dt + molecule[index].position() % (molecule.orientation() + molecule.angular_velocity() * dt);
  }
};

#endif
