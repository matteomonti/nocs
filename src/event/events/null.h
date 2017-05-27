// Foward declarations

namespace events
{
  class null;
};

#if !defined(__forward__) && !defined(__nobb__event__events__null__h)
#define __nobb__event__events__null__h

// Forward includes

#define __forward__
#include "engine/engine.h"
#undef __forward__

// Includes

#include "event/event.h"

namespace events
{
  class null : public event
  {
    // Constructors

    null();

    // Methods

    bool current();
    bool resolve();
    void each(engine *, void (engine :: *)(molecule &));

    // Operators

    bool operator == (const event &) const;
  };
};

#endif
