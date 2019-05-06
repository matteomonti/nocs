// Forward declarations

template <typename> class report;

#if !defined(__forward__) && !defined(__nobb__event__reports__molecule__h)
#define __nobb__event__reports__molecule__h

// Libraries

#include <stddef.h>

// Includes

#include "geometry/vec.h"

// Forward includes

#define __forward__
#include "event/events/molecule.h"
#undef __forward__

template <> class report <events :: molecule>
{
  // Public nested classes

public:

  class alpha
  {
    // Public nested classes

  public:

    class velocity
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      velocity(const events :: molecule &);

      // Getters

      const vec & before() const;
      const vec & after() const;
            vec delta() const;

    } velocity;

    class momentum
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      momentum(const events :: molecule &);

      // Getters

      const vec & before() const;
            vec after() const;
            vec delta() const;

    } momentum;

    class angular_velocity
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      angular_velocity(const events :: molecule &);

      // Getters

      const double & before() const;
      const double & after() const;
            double delta() const;

    } angular_velocity;

    class angular_momentum
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      angular_momentum(const events :: molecule &);

      // Getters

      const double & before() const;
            double after() const;
            double delta() const;

    } angular_momentum;

    class energy
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      energy(const events :: molecule &);

      // Getters

      double before() const;
      double after() const;
      double delta() const;

    } energy;

  private:

    // Members

    const events :: molecule & _event;

  public:

    // Constructors

    alpha(const events :: molecule &);

    // Getters

    const size_t & id() const;
    const size_t & atom() const;
    const vec & position() const;
    const double & orientation() const;
    const double & mass() const;

  } alpha;

  class beta
  {
    // Public nested classes

  public:

    class velocity
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      velocity(const events :: molecule &);

      // Getters

      const vec & before() const;
      const vec & after() const;
            vec delta() const;

    } velocity;

    class momentum
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      momentum(const events :: molecule &);

      // Getters

      const vec & before() const;
            vec after() const;
            vec delta() const;

    } momentum;

    class angular_velocity
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      angular_velocity(const events :: molecule &);

      // Getters

      const double & before() const;
      const double & after() const;
            double delta() const;

    } angular_velocity;

    class angular_momentum
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      angular_momentum(const events :: molecule &);

      // Getters

      const double & before() const;
            double after() const;
            double delta() const;

    } angular_momentum;

    class energy
    {
      // Members

      const events :: molecule & _event;

    public:

      // Constructors

      energy(const events :: molecule &);

      // Getters

      double before() const;
      double after() const;
      double delta() const;

    } energy;

  private:

    // Members

    const events :: molecule & _event;

  public:

    // Constructors

    beta(const events :: molecule &);

    // Getters

    const size_t & id() const;
    const size_t & atom() const;
    const vec & position() const;
    const double & orientation() const;
    const double & mass() const;

  } beta;

private:

  // Members

  const events :: molecule & _event;

public:

  // Constructors

  report(const events :: molecule &);

  // Getters

  const double & time() const;
  const double & module() const;
};

#endif
