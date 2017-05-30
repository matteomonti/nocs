// Forward declarations

class engine;

#if !defined(__forward__) && !defined(__nobb__engine__engine__h)
#define __nobb__engine__engine__h

// Libraries

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <type_traits>

// Forward includes

#define __forward__
#include "molecule/molecule.h"
#include "elements/bumper.h"
#undef __forward__

// Includes

#include "data/heap.hpp"
#include "data/hashtable.hpp"
#include "data/set.hpp"
#include "grid.hpp"
#include "event/event.h"

class engine
{
public:

  // Nested classes

  class tag
  {
    // Settings

    static constexpr size_t tags = 8;

    // Friends

    friend class engine;

    // Members

    size_t _id;
    uint8_t _tags[tags];
    size_t _references;

  public:

    // Constructors

    tag();

    // Getters

    const size_t & id() const;
    size_t size() const;

  private:

    // Private methods

    void add(const uint8_t &);
    void remove(const uint8_t &);

    // Private operators

    void operator ++ ();
    void operator ++ (int);

    void operator -- ();
    void operator -- (int);

    // Static members

    static size_t autoincrement;
  };

private:

  // Members

  heap <event :: wrapper> _events;
  grid _grid;

  hashtable <size_t, molecule *> _molecules;
  set <bumper *> _bumpers;

  double _time;

public:

  // Constructors

  engine(const size_t &);

  // Getters

  const size_t & fineness() const;

  // Methods

  size_t add(const molecule &);
  void remove(const size_t &);

  void run(const double &);

  template <typename type, typename lambda, typename std :: enable_if <std :: is_same <type, molecule> :: value> :: type * = nullptr> void each(const lambda &) const; // TODO: Add validation for lambda

private:

  // Private methods

  void refresh(molecule &, const size_t & = 0);

  void incref(molecule &, const size_t &);
  void decref(molecule &, const size_t &);
};

#endif
