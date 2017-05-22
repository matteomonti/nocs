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

    // Getters

    :: molecule & alpha();
    size_t alpha_atom();

    :: molecule & beta();
    size_t beta_atom();

    // Methods

    bool current();
    void resolve();

  private:

    // Private methods

    void print() const;

    double collision(const :: molecule &, const size_t &, const :: molecule &, const size_t &, const double &, const double &, const int & = vec :: direct);

    // Static private methods

    static inline vec position(const :: molecule &, const size_t &, const int & = vec :: direct);
    static inline vec position(const :: molecule &, const size_t &, const double &, const int & = vec :: direct);
  };
};
#endif
