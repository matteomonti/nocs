// Forward declarations

class grid;

#if !defined(__forward__) && !defined(__nobb__engine__grid__h)
#define __nobb__engine__grid__h

// Libraries

#include <stddef.h>

// Forward includes

#define __forward__
#include "molecule/molecule.h"
#undef __forward__

// Includes

#include "data/set.hpp"

class grid
{
public:

  // Nested classes

  class mark
  {
    // Friends

    friend class grid;

    // Members

    size_t x;
    size_t y;
  };

private:

  // Members

  size_t _fineness;

  set <molecule *> ** _molecules;

  // Constructors

  grid(const size_t &);

  // Destructor

  ~grid();

  // Getters

  size_t fineness() const;

  // Methods

  void add(molecule &);
  void remove(molecule &);
  void update(molecule &);
};

#endif
