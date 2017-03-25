#include "wall.h"

// Constructors

wall :: wall() : event()
{
}

wall :: wall(molecule * m1) : event(), _m1(m1)
{
  e = this->_m->version();
  /* Scocca la mezzanotte, ora di andare a dormire */
}
