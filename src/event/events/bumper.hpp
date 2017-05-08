#ifndef __nobb__event__events__bumper__hpp
#define __nobb__event__events__bumper__hpp

#include "bumper.h"
#include "math/gss.hpp"
#include "math/secant.hpp"

namespace events
{
  // Static private methods

  inline vec bumper :: position(const molecule & molecule, const size_t & index)
  {
    return molecule.position() + (molecule[index].position() % molecule.orientation());
  }

  inline vec bumper :: position(const molecule & molecule, const size_t & index, const double & time)
  {
    double dt = time - molecule.time();
    return molecule.position() + molecule.velocity() * dt + molecule[index].position() % (molecule.orientation() + molecule.angular_velocity() * dt);
  }
}

#endif
