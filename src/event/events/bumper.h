// Foward declarations

namespace events
{
  class bumper;
};

#if !defined(__forward__) && !defined(__nobb__event__events__bumper__h)
#define __nobb__event__events__bumper__h

// Libraries

#include <cmath>

// Forward includes

#define __forward__
#include "engine/engine.h"
#include "event/reports/bumper.h"
#undef __forward__

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
    // Settings

    static constexpr double time_epsilon = 1.e-9;
    
    // Friends

    friend class report <events :: bumper>;

    // Members

    struct
    {
      :: molecule * molecule;
      unsigned int version;
      size_t atom;
    } _molecule;

    :: bumper * _bumper;
    int _fold;

    // Working members

    vec v;
    vec p;
    double av;
    double l;
    vec r;
    double module;

  public:

    // Constructors

    bumper(:: molecule &, const int &, :: bumper &);

    // Getters

    const :: molecule & molecule() const;

    // Methods

    bool current();
    bool resolve();
    void each(engine *, void (engine :: *)(:: molecule &, const size_t &));
    void callback(dispatcher &);

    // Private methods

    std :: ostream & print(std :: ostream &) const;

    double collision(const :: molecule &, const size_t &, const :: bumper &, const double &, const double &, const int & = vec :: direct);

    // Static private methods

    static inline vec position(const :: molecule &, const size_t &, const int &);
    static inline vec position(const :: molecule &, const size_t &, const double &, const int &);
  };
};

#endif
