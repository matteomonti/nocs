// Foward declarations

class wall;

#if !defined(__forward__) && !defined(__nobb__event__wall__h)
#define __nobb__event__wall__h

// Libraries

#include <iostream>
#include <cmath>

// Includes

#include "/molecule/molecule.h"
#include "/physics/constants.h"

/*IMPLEMENTAZIONE BASIC DI URTO TRA MOLECOLA E MURO*/

/* NOTE :: si hanno da implementare sia pareti ideali elastiche sia teletrasportatori stile mondo toroidale di Snake */

class wall : private event
{
  // Enums

  enum side {up, down, left, right};

  // Members

  molecule * _m;
  unsigned int _e;
  side _s;

public:

  // Constructors

  wall();
  wall(molecule *);

};

#endif
