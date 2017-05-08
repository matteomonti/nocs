#include "grid.h"
#include "molecule/molecule.h"

// Nested classes

// mark

// Getters

size_t grid :: mark :: x() const
{
  return this->_x;
}

size_t grid :: mark :: y() const
{
  return this->_y;
}

// grid

// Constructors

grid :: grid(const size_t & fineness) : _fineness(fineness)
{
  this->_molecules = new set <molecule *> * [this->_fineness];

  for(size_t i = 0; i < this->_fineness; i++)
    this->_molecules[i] = new set <molecule *> [this->_fineness];

  this->_bumpers = new set <bumper *> * [this->_fineness];

  for(size_t i = 0; i < this->_fineness; i++)
    this->_bumpers[i] = new set <bumper *> [this->_fineness];
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
  molecule.mark._x = (size_t) (molecule.position().x * this->_fineness);
  molecule.mark._y = (size_t) (molecule.position().y * this->_fineness);

  this->_molecules[molecule.mark._x][molecule.mark._y].add(&molecule);
}

void grid :: add(bumper & bumper)
{
  this->_bumpers[(size_t) bumper.position().x * this->_fineness][(size_t) bumper.position().y * this->_fineness].add(&bumper);
}

void grid :: remove(molecule & molecule)
{
  this->_molecules[molecule.mark._x][molecule.mark._y].remove(&molecule);
}

void grid :: update(molecule & molecule)
{
  this->remove(molecule);
  this->add(molecule);
}

void grid :: update(molecule & molecule, const size_t & x, const size_t & y)
{
  this->remove(molecule);
  this->add(molecule, x, y);
}

// Private Methods

void grid :: add(molecule & molecule, const size_t & x, const size_t & y)
{
  molecule.mark._x = x;
  molecule.mark._y = y;

  this->_molecules[molecule.mark._x][molecule.mark._y].add(&molecule);
}
