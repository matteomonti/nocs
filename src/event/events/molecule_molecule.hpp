#ifndef __nobb__event__events__molecule_molecule__hpp
#define __nobb__event__events__molecule_molecule__hpp

#include "molecule_molecule.h"
#include "math/gss.hpp"

namespace events
{
  // Private methods

  inline vec molecule_molecule :: position(const molecule & molecule, const size_t & index, const double & time)
  {
    double dt = time - molecule.time();
    return molecule.position() + molecule.velocity() * dt + molecule[index].position() % (molecule.orientation() + molecule.angular_velocity() * dt);
  }
};

#endif
