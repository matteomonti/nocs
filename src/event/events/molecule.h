// Foward declarations

namespace events
{
  class molecule;
};

#if !defined(__forward__) && !defined(__nobb__event__events__molecule__h)
#define __nobb__event__events__molecule__h

// Libraries

#include <iostream>
#include <cmath>
#include <math.h>

// Forward includes

#define __forward__
#include "engine/engine.h"
#undef __forward__


// Includes

#include "molecule/molecule.h"
#include "math/newton.h"
#include "math/gss.h"
#include "math/secant.h"
#include "event/event.h"

namespace events
{
  class molecule : public event
  {
    // Settings

    static constexpr double time_epsilon = 1.e-9;

    // Members

    struct
    {
      :: molecule * molecule;
      size_t atom;
      unsigned int version;
      int fold;
    } _alpha;

    struct
    {
      :: molecule * molecule;
      size_t atom;
      unsigned int version;
    } _beta;

  public:

    // Constructors

    molecule(:: molecule &, const int &, :: molecule &);

    // Methods

    bool current();
    bool resolve();
    void each(engine *, void (engine :: *)(:: molecule &, const size_t &));
    void callback(dispatcher &);

  private:

    // Private methods

    std :: ostream & print(std :: ostream &) const;

    double collision(const :: molecule &, const size_t &, const :: molecule &, const size_t &, const double &, const double &, const int & = vec :: direct);

    // Static private methods

    static inline vec position(const :: molecule &, const size_t &, const int & = vec :: direct);
    static inline vec position(const :: molecule &, const size_t &, const double &, const int & = vec :: direct);
  };
};
#endif
