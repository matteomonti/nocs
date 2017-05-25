// Forward declarations

#if !defined(__forward__) && !defined(__nobb__engine__engine__h)
#define __nobb__engine__engine__h

// Libraries

#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Forward includes

#define __forward__
#include "molecule/molecule.h"
#include "elements/bumper.h"
#undef __forward__

// Includes

#include "data/heap.hpp"
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
    bool alive() const;
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

  set <molecule *> _molecules;
  set <bumper *> _bumpers;

public:

  // Constructors

  engine(const size_t &);

private:

  // Private methods

  void refresh(molecule &);
};

#endif
