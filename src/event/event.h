// Foward declarations

class event;

#if !defined(__forward__) && !defined(__nobb__event__event__h)
#define __nobb__event__event__h

// Libraries

#include <iostream>
#include <limits>

class event
{
protected:

  // Protected Members

  bool _happens;
  double _time;

public:

  // Getters

  bool happens();
  double time();

  // Public Methods

  virtual bool current() = 0;
  virtual void resolve() = 0;

  // Standard Output

  friend std :: ostream & operator << (std :: ostream &, const event &);

  // Private Methods

  virtual void print() const = 0;

};

#endif
