// Forward declarations

class grid;

#if !defined(__forward__) && !defined(__nobb__engine__grid__h)
#define __nobb__engine__grid__h

// Includes

#include "molecule/molecule.h"

class grid
{
  // Members

  size_t _fineness;
  
  // Getters

  size_t fineness() const;
};

#endif
