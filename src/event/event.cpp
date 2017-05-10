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

// Standard Output

std :: ostream & operator << (std :: ostream & out, const event & event)
{
  event.print();
  return out;
}
