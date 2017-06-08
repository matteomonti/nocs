// Foward declarations

class event;

#if !defined(__forward__) && !defined(__nobb__event__event__h)
#define __nobb__event__event__h

// Libraries

#include <iostream>
#include <limits>

// Forward includes

#define __forward__
#include "engine/engine.h"
#include "molecule/molecule.h"
#undef __forward__

class event
{
public:

  // Nested classes

  class wrapper
  {
    // Members

    event * _event;

public:

    // Constructors

    wrapper();
    wrapper(event *);

    // Operators

    bool operator > (const wrapper &) const;
    bool operator >= (const wrapper &) const;
    bool operator < (const wrapper &) const;
    bool operator <= (const wrapper &) const;

    // Casting

    operator event * ();
    operator const event * () const;
  };

protected:

  // Protected Members

  bool _happens;
  double _time;

public:

  // Getters

  bool happens() const;
  double time() const;

  // Public Methods

  virtual bool current() = 0;
  virtual bool resolve() = 0;
  virtual void each(engine *, void (engine :: *)(molecule &, const size_t &)) = 0;

  // Standard Output

  friend std :: ostream & operator << (std :: ostream &, const event &);

  // Private Methods

  virtual std :: ostream & print(std :: ostream &) const;

};

#endif
