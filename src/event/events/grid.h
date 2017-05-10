// Foward declarations

namespace events
{
  class grid;
};

#if !defined(__forward__) && !defined(__nobb__event__events__grid__h)
#define __nobb__event__events__grid__h

// Libraries

#include <cmath>

// Includes

#include "molecule/molecule.h"
#include "engine/grid.h"
#include "event/event.h"
#include "math/newton.h"
#include "math/gss.h"
#include "math/secant.h"

namespace events
{
  class grid : public event
  {
    // Members

    struct
    {
      molecule * molecule;
      unsigned int version;
      size_t new_x;
      size_t new_y;
    } _molecule;

    :: grid * _grid;

    vec :: fold _fold;

  public:

    // Constructors

    grid(molecule &, :: grid &);

    // Getters

    molecule & mol();

    // Methods

    bool current();
    void resolve();

  private:

    // Private Methods

    void print() const;
  };
};

#endif
