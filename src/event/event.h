// Foward declarations

class event;

#if !defined(__forward__) && !defined(__nobb__event__event__h)
#define __nobb__event__event__h

// Libraries

#include <iostream>
#include <cmath>

class event
{
protected:

  // Protected Members

  bool _happens;
  double _time;

public:

  // Constructors

  event();

  // Getters

  bool happens();
  double time();

  // Public Methods

  virtual void compute();
  virtual bool current();
};

#endif
