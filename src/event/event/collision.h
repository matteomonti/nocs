// Foward declarations

class collision;

#if !defined(__forward__) && !defined(__nobb__event__collision__h)
#define __nobb__event__collision__h

// Libraries

#include <iostream>
#include <cmath>

// Includes

#include "/molecule/molecule.h"


class collision : private event
{
  // Members

  molecule * _m1;
  unsigned int _e1;
  molecule * _m2;
  unsigned int _e2;

public:

  // Constructors

  collision();
  collision(molecule *, molecule *);

};

#endif
