#include "grid.h"

namespace events
{
  // Constructors

  grid :: grid (molecule & molecule, :: grid & grid)
  {
    this->_happens = true;

    double time = molecule.time();

    this->_fold = vec :: direct;

    double time_x = std :: numeric_limits <double> :: infinity();
    double time_y = std :: numeric_limits <double> :: infinity();

    double step = 1. / grid.fineness();

    if(molecule.velocity().x > 0)
      time_x = (step * (molecule.mark.x() + 1) - molecule.position().x) / molecule.velocity().x;
    else if(molecule.velocity().x != 0)
      time_x = (step * molecule.mark.x() - molecule.position().x) / molecule.velocity().x;

    if(molecule.velocity().y > 0)
      time_y = (step * (molecule.mark.y() + 1) - molecule.position().y) / molecule.velocity().y;
    else if(molecule.velocity().y != 0)
      time_y = (step * molecule.mark.y() - molecule.position().y) / molecule.velocity().y;

    // Is teleporting necessary?

    if(time_x == std :: numeric_limits <double> :: infinity() && time_y == std :: numeric_limits <double> :: infinity())
      this->_happens = false;

    else if(time_x < time_y)
    {
      this->_time = time_x + time;

      if(molecule.velocity().x > 0)
      {
        this->_molecule.new_x = molecule.mark.x() + 1;
        if(molecule.mark.x() == grid.fineness() - 1)
        {
          this->_molecule.new_x = 0;
          this->_fold = vec :: left;
        }
      }
      else if(molecule.velocity().x < 0)
      {
        this->_molecule.new_x = molecule.mark.x() - 1;
        if(molecule.mark.x() == 0)
        {
          this->_molecule.new_x = grid.fineness() - 1;
          this->_fold = vec :: right;
        }
      }
      this->_molecule.new_y = molecule.mark.y();
    }
    else
    {
      this->_time = time_y + time;

      if(molecule.velocity().y > 0)
      {
        this->_molecule.new_y = molecule.mark.y() + 1;
        if(molecule.mark.y() == grid.fineness() - 1)
        {
          this->_molecule.new_y = 0;
          this->_fold = vec :: down;
        }
      }
      else if(molecule.velocity().y < 0)
      {
        this->_molecule.new_y = molecule.mark.y() - 1;
        if(molecule.mark.y() == 0)
        {
          this->_molecule.new_y = grid.fineness() - 1;
          this->_fold = vec :: up;
        }
      }
      this->_molecule.new_x = molecule.mark.x();
    }

    // Shall we leave the recollocation to the update method or should we note the new collocation in this point and remove the _fold?

    this->_molecule.molecule = &molecule;
    this->_molecule.version = molecule.version();
    this->_grid = &grid;
  }

  // Getters

  molecule & grid :: mol()
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
    this->_molecule.molecule->teleport(this->_fold);
    this->_grid->update(*(this->_molecule.molecule), this->_molecule.new_x, this->_molecule.new_y);
  }

  // Private Methods

  void grid :: print() const
  {
    std :: cout << "Event grid at time: " << this->_time;
  }
};
