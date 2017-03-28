// Foward declarations

class collision;

#if !defined(__forward__) && !defined(__nobb__event__event__collision__h)
#define __nobb__event__event__collision__h

// Libraries

#include <iostream>
#include <cmath>

// Includes

#include "/molecule/molecule.h"

class collision : private event
{
  // Members

  struct
  {
    molecule * molecule;
    unsigned int version;
  } _alpha;

  struct
  {
    molecule * molecule;
    unsigned int version;
  } _beta;

public:

  // Constructors

  collision(molecule *, molecule *);

  // Methods

  bool current();
  void resolve();
};

#endif
