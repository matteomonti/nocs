// Foward declarations

class collision;

#if !defined(__forward__) && !defined(__nobb__event__collision__h)
#define __nobb__event__collision__h

// Libraries

#include <iostream>
#include <cmath>

// Includes

#include "/molecule/molecule.h"

/* IMPLEMENTAZIONE TEMPORANEA BASIC DI URTO TRA DUE MOLECOLE */

/* NOTE :: questa classe tiene "sottomano" le due molecole che intende analizzare con due puntatori. In questo modo può tener traccia dei loro progressi e, se necessario, integrare il loro moto fino all'evento in questione*/

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
