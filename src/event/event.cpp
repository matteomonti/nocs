#include "event.h"

// Getters

bool event :: happens()
{
  return this->_happens;
}

double event :: time()
{
  return this->_time;
}

// Public Methods

virtual void event :: compute() = 0;
virtual bool event :: current() = 0;
