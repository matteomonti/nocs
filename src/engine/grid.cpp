#include "grid.h"
#include "molecule/molecule.h"

// Constructors

grid :: grid(const size_t & fineness) : _fineness(fineness)
{
  this->_molecules = new set <molecule *> * [this->_fineness];

  for(size_t i = 0; i < this->_fineness; i++)
    this->_molecules[i] = new set <molecule *> [this->_fineness];
}

// Destructor

grid :: ~grid()
{
  for(size_t i = 0; i < this->_fineness; i++)
    delete [] this->_molecules[i];

  delete [] this->_molecules;
}

// Getters

size_t grid :: fineness() const
{
  return this->_fineness;
}

// Methods

void grid :: add(molecule & molecule)
{
  molecule.mark.x = (size_t) (molecule.position().x * this->_fineness);
  molecule.mark.y = (size_t) (molecule.position().y * this->_fineness);

  this->_molecules[molecule.mark.x][molecule.mark.y].add(&molecule);
}

void grid :: remove(molecule & molecule)
{
  this->_molecules[molecule.mark.x][molecule.mark.y].remove(&molecule);
}

void grid :: update(molecule & molecule)
{
  this->remove(molecule);
  this->add(molecule);
}
