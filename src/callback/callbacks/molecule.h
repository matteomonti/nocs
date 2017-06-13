// Forward declarations

template <typename, typename = void> class callback;

#if !defined(__forward__) && !defined(__nobb__callback__callbacks__molecule__h)
#define __nobb__callback__callbacks__molecule__h

// Forward includes

#define __forward__
#include "event/events/molecule.h"
#undef __forward__

template <> class callback <events :: molecule, void>
{
public:

  // Methods

  virtual void trigger(const events :: molecule &) = 0;
};

template <typename lambda> class callback <events :: molecule, lambda> : public callback <events :: molecule, void>
{
  // Members

  lambda _callback;

public:

  // Constructors

  callback(const lambda &);

  // Methods

  void trigger(const events :: molecule &);
};

#endif
