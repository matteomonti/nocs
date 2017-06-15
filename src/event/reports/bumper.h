// Forward declarations

template <typename> class report;

#if !defined(__forward__) && !defined(__nobb__event__reports__bumper__h)
#define __nobb__event__reports__bumper__h

// Libraries

#include <stddef.h>

// Includes

#include "geometry/vec.h"

// Forward includes

#define __forward__
#include "event/events/bumper.h"
#undef __forward__

template <> class report <events :: bumper>
{
  // Public nested classes

public:

  class velocity
  {
    // Members

    const events :: bumper & _event;

  public:

    // Constructors

    velocity(const events :: bumper &);

    // Getters

    const vec & before() const;
    const vec & after() const;
    const vec delta() const;

  } velocity;

  class momentum
  {
    // Members

    const events :: bumper & _event;

  public:

    // Constructors

    momentum(const events :: bumper &);

    // Getters

    const vec & before() const;
    const vec after() const;
    const vec delta() const;

  } momentum;

  class angular_velocity
  {
    // Members

    const events :: bumper & _event;

  public:

    // Constructors

    angular_velocity(const events :: bumper &);

    // Getters

    const double & before() const;
    const double & after() const;
    const double delta() const;

  } angular_velocity;

  class angular_momentum
  {
    // Members

    const events :: bumper & _event;

  public:

    // Constructors

    angular_momentum(const events :: bumper &);

    // Getters

    const double & before () const;
    const double after() const;
    const double delta() const;

  } angular_momentum;

  class energy
  {
    // Members

    const events :: bumper & _event;

  public:

    // Constructors

    energy(const events :: bumper &);

    // Getters

    const double before() const;
    const double after() const;
    const double delta() const;

  } energy;

  class bumper
  {
    // Members

    const events :: bumper & _event;

  public:

    // Constructors

    bumper(const events :: bumper &);

    // Getters

    const vec & position() const;
    const double & radius() const;

  } bumper;

private:

  // Members

  const events :: bumper & _event;

public:

  // Constructors

  report(const events :: bumper &);

  // Getters

  const size_t & id() const;
  const size_t & atom() const;
  const vec & position() const;
  const double & orientation() const;
  const double & mass() const;
  const double & time() const;
  const double & module() const;
};

#endif
