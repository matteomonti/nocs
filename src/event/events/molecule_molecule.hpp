#ifndef __nobb__event__events__molecule_molecule__hpp
#define __nobb__event__events__molecule_molecule__hpp

#include "molecule_molecule.h"

namespace events
{
  // Private methods

  inline vec molecule_molecule :: atom_position(const molecule & molecule, const size_t & index, const double & time)
  {
    double dt = time - molecule.time();
    return molecule.position() + molecule.velocity() * dt + molecule[index].position() % (molecule.orientation() + molecule.angular_velocity() * dt);
  }

  inline double molecule_molecule :: atoms_squared_distance(const molecule & alpha, const size_t & alpha_index, const molecule & beta, const size_t & beta_index, const double & time)
  {
    return ~(this->atom_position(alpha, alpha_index, time) - this->atom_position(beta, beta_index, time));
  }
};

#endif
