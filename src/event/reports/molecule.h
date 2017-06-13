// Forward declarations

namespace reports
{
  class molecule;
};

#if !defined(__forward__) && !defined(__nobb__event__reports__molecule__h)
#define __nobb__event__reports__molecule__h

// Libraries

#include <stddef.h>

// Forward includes

#define __forward__
#include "event/events/molecule.h"
#undef __forward__

namespace reports
{
  class molecule
  {
    // Members

    const events :: molecule & _event;

public:

    // Constructors

    molecule(const events :: molecule &);

    // Getters

    const size_t & alpha() const;
    const size_t & beta() const;
  };
};

#endif
