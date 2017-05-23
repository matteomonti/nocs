#include "grid.h"

namespace events
{
  // Constructors

  grid :: grid (:: molecule & molecule, :: grid & grid)
  {
    double time = molecule.time();
    double step = 1. / grid.fineness();

    double time_x = (step * (molecule.mark.x() + (size_t)(molecule.velocity().x >= 0)) - molecule.position().x) / molecule.velocity().x;
    double time_y = (step * (molecule.mark.y() + (size_t)(molecule.velocity().y >= 0)) - molecule.position().y) / molecule.velocity().y;

    if(!std :: isfinite(time_x)) time_x = std :: numeric_limits <double> :: infinity();
    if(!std :: isfinite(time_y)) time_y = std :: numeric_limits <double> :: infinity();

    if(!std :: isfinite(time_x) && !std :: isfinite(time_y))
    {
      this->_happens = false;
      return;
    }

    if(time_x < time_y)
      this->_fold = (molecule.velocity().x > 0) ? vec :: right : vec :: left;
    else
      this->_fold = (molecule.velocity().y > 0) ? vec :: up : vec :: down;

    this->_happens = true;
    this->_time = molecule.time() + std :: min(time_x, time_y);
    this->_molecule.molecule = &molecule;
    this->_molecule.version = molecule.version();
    this->_grid = &grid;
  }

  // Getters

  molecule & grid :: molecule()
  {
    return *(this->_molecule.molecule);
  }

  // Methods

  bool grid :: current()
  {
    return this->_molecule.version == this->_molecule.molecule->version();
  }

  void grid :: resolve()
  {
    // Check version

    if(!current())
      return;

    // Update version

    (*(this->_molecule.molecule))++;

    // Integrate, teleport, resolve

    this->_molecule.molecule->integrate(this->_time);
    this->_grid->update(*(this->_molecule.molecule), this->_fold);
  }

  // Private Methods

  std :: ostream & grid :: print(std :: ostream & out) const
  {
    out << "Event grid at time: " << this->_time;
    return out;
  }
};
