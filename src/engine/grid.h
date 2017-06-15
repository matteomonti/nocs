// Forward declarations

class grid;

#if !defined(__forward__) && !defined(__nobb__engine__grid__h)
#define __nobb__engine__grid__h

// Libraries

#include <stddef.h>
#include <type_traits>

// Forward includes

#define __forward__
#include "molecule/molecule.h"
#include "elements/bumper.h"
#undef __forward__

// Includes

#include "geometry/vec.h"
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

    size_t _x;
    size_t _y;

  public:

    // Getters

    size_t x() const;
    size_t y() const;
  };

private:

  // Members

  size_t _fineness;

  set <molecule *> ** _molecules;
  set <bumper *> ** _bumpers;

public:

  // Constructors

  grid(const size_t &);

  // Destructor

  ~grid();

  // Getters

  const size_t & fineness() const;

  // Methods

  void add(molecule &);
  void add(bumper &);
  void remove(molecule &);
  void update(molecule &, const vec :: fold &);

  template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type * = nullptr> void each(const size_t &, const size_t &, const lambda &); // TODO: Add validation for lambda
  template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, bumper> :: value> :: type * = nullptr> void each(const size_t &, const size_t &, const lambda &); // TODO: Add validation for lambda

private:

  // Private methods

  void add(molecule &, const size_t &, const size_t &);
  void add(bumper &, const size_t &, const size_t &);
};

#endif
