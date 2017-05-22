// Foward declarations

namespace events
{
  class bumper;
};

#if !defined(__forward__) && !defined(__nobb__event__events__bumper__h)
#define __nobb__event__events__bumper__h

// Libraries

#include <cmath>

// Includes

#include "molecule/molecule.h"
#include "elements/bumper.h"
#include "event/event.h"
#include "math/newton.h"
#include "math/gss.h"
#include "math/secant.h"

namespace events
{
  class bumper : public event
  {
    // Members

    struct
    {
      molecule * molecule;
      unsigned int version;
      size_t atom;
    } _molecule;

    :: bumper * _bumper;
    int _fold;

  public:

    // Constructors

    bumper(molecule &, const int &, :: bumper &);

    // Getters

    molecule & molecule();

    // Methods

    bool current();
    void resolve();

    // Private Methods

    void print() const;

    double collision(const molecule &, const size_t &, const :: bumper &, const double &, const double &, const int & = vec :: direct);

    // Static private methods

    static inline vec position(const molecule &, const size_t &, const int &);
    static inline vec position(const molecule &, const size_t &, const double &, const int &);
  };
};

#endif
