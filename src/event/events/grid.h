// Foward declarations

namespace events
{
  class grid;
};

#if !defined(__forward__) && !defined(__nobb__event__events__grid__h)
#define __nobb__event__events__grid__h

// Libraries

#include <cmath>
#include <typeinfo>

// Forward includes

#define __forward__
#include "engine/engine.h"
#undef __forward__

// Includes

#include "molecule/molecule.h"
#include "engine/grid.h"
#include "event/event.h"
#include "math/newton.h"
#include "math/gss.h"
#include "math/secant.h"
#include "engine/engine.h"

namespace events
{
  class grid : public event
  {
    // Members

    struct
    {
      molecule * molecule;
      unsigned int version;
    } _molecule;

    :: grid * _grid;
    vec :: fold _fold;

  public:

    // Constructors

    grid(:: molecule &, :: grid &);

    // Methods

    bool current();
    bool resolve();
    void each(engine *, void (engine :: *)(:: molecule &));

  private:

    // Private Methods

    std :: ostream & print(std :: ostream &) const;

  public:

    // Operators

    bool operator == (const event &) const;
  };
};

#endif
