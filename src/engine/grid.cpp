#include "grid.hpp"
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
  this->add(molecule, (size_t) (molecule.position().x * this->_fineness), (size_t) (molecule.position().y * this->_fineness));
}

void grid :: add(bumper & bumper)
{
  this->_bumpers[(size_t) (bumper.position().x * this->_fineness)][(size_t) (bumper.position().y * this->_fineness)].add(&bumper);
}

void grid :: remove(molecule & molecule)
{
  this->_molecules[molecule.mark._x][molecule.mark._y].remove(&molecule);
}

void grid :: update(molecule & molecule, const vec :: fold & fold)
{
  this->remove(molecule);

  vec :: fold teleport = vec :: direct;

  size_t x = molecule.mark.x();
  size_t y = molecule.mark.y();

  switch (fold)
  {
    case vec :: left:
    {
      x = (this->_fineness + x - 1) % this->_fineness;
      if(x == this->_fineness - 1) teleport = vec :: right;
      break;
    }
    case vec :: right:
    {
      x = (x + 1) % this->_fineness;
      if(x == 0) teleport = vec :: left;
      break;
    }
    case vec :: up:
    {
      y = (y + 1) % this->_fineness;
      if(y == 0) teleport = vec :: down;
      break;
    }
    case vec :: down:
    {
      y = (this->_fineness + y - 1) % this->_fineness;
      if(y == this->_fineness - 1) teleport = vec :: up;
      break;
    }
  }

  molecule.teleport(teleport);
  this->add(molecule, x, y);
}

// Private Methods

void grid :: add(molecule & molecule, const size_t & x, const size_t & y)
{
  molecule.mark._x = x;
  molecule.mark._y = y;

  this->_molecules[molecule.mark._x][molecule.mark._y].add(&molecule);
}
