// Foward declarations

namespace events
{
  class molecule_molecule;
};

#if !defined(__forward__) && !defined(__nobb__event__events__molecule_molecule__h)
#define __nobb__event__events__molecule_molecule__h

// Libraries

#include <iostream>
#include <cmath>
#include <math.h>

// Includes

#include "molecule/molecule.h"
#include "math/newton.h"
#include "math/gss.h"
#include "math/secant.h"
#include "event/event.h"

namespace events
{
  class molecule_molecule : private event
  {
    // Members

    struct
    {
      molecule * molecule;
      unsigned int version;
    } _alpha;

    struct
    {
      molecule * molecule;
      unsigned int version;
    } _beta;

  public:

    // Constructors

    molecule_molecule(molecule &, molecule &);

    // Methods

    bool current();
    void resolve();

    // Private methods

    static inline vec position(const molecule &, const size_t &, const double &);
    double collision(const molecule &, const size_t &, const molecule &, const size_t &, const double &, const double &, const double &);
  };
};
#endif
