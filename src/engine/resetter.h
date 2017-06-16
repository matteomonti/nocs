// Forward declarations

class resetter;

#if !defined(__forward__) && !defined(__nobb__engine__resetter__h)
#define __nobb__engine__resetter__h

// Libraries

#include <stddef.h>
#include <stdint.h>

// Forward includes

#define __forward__
#include "engine.h"
#undef __forward__

class resetter
{
  // Friends

  friend class engine;

  // Service nested classes

  class energy
  {
    // Members

    engine & _engine;

  public:

    // Constructors

    energy(engine &);

    // Methods

    void id(const size_t &, const double &);
    void tag(const uint8_t &, const double &);
    void all(const double &);
  };

  // Members

  engine & _engine;

public:

  // Public members

  energy energy;

private:

  // Private constructors

  resetter(engine &);
};

#endif
