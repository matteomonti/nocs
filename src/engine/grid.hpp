#ifndef __nobb__engine__grid__hpp
#define __nobb__engine__grid__hpp

#include "grid.h"

// Methods

template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type *> void grid :: each(const size_t & x, const size_t & y, const lambda & callback)
{
  this->_molecules[x][y].each([&](molecule * molecule)
  {
    callback(*molecule);
  });
}

template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, bumper> :: value> :: type *> void grid :: each(const size_t & x, const size_t & y, const lambda & callback)
{
  this->_bumpers[x][y].each([&](bumper * bumper)
  {
    callback(*bumper);
  });
}

#endif
