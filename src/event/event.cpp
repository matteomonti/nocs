#include "event.h"

// wrapper

// Constructors

event :: wrapper :: wrapper()
{
}

event :: wrapper :: wrapper(event * event) : _event(event)
{
}

// Operators

bool event :: wrapper :: operator > (const wrapper & rho) const
{
  return this->_event->time() > rho._event->time();
}

bool event :: wrapper :: operator >= (const wrapper & rho) const
{
  return this->_event->time() >= rho._event->time();
}

bool event :: wrapper :: operator < (const wrapper & rho) const
{
  return this->_event->time() < rho._event->time();
}

bool event :: wrapper :: operator <= (const wrapper & rho) const
{
  return this->_event->time() <= rho._event->time();
}

// Casting

event :: wrapper :: operator event * ()
{
  return this->_event;
}

event :: wrapper :: operator const event * () const
{
  return this->_event;
}

// event

// Getters

bool event :: happens() const
{
  return this->_happens;
}

double event :: time() const
{
  return this->_time;
}

// Standard Output

std :: ostream & operator << (std :: ostream & out, const event & event)
{
  return event.print(out);
}

// Private Methods

std :: ostream & event :: print(std :: ostream & out) const
{
  out << "Event at time: " << this->_time;
  return out;
}
