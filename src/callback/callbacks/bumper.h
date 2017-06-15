// Forward declarations

#ifndef __nobb__callback__callbacks__callbackforward
#define __nobb__callback__callbacks__callbackforward

template <typename, typename = void> class callback;

#endif

#if !defined(__forward__) && !defined(__nobb__callback__callbacks__bumper__h)
#define __nobb__callback__callbacks__bumper__h

// Forward includes

#define __forward__
#include "event/events/bumper.h"
#undef __forward__

template <> class callback <events :: bumper, void>
{
public:

  // Methods

  virtual void trigger(const events :: bumper &) = 0;
};

template <typename lambda> class callback <events :: bumper, lambda> : public callback <events :: bumper, void>
{
  // Members

  lambda _callback;

public:

  // Constructors

  callback(const lambda &);

  // Methods

  void trigger(const events :: bumper &);
};

#endif
