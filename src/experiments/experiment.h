// Forward declarations

#if !defined(__forward__) && !defined(__nobb__experiments__experiment__h)
#define __nobb__experiments__experiment__h

// Libraries

#include <iostream>
#include <iomanip>
#include <random>
#include <fstream>

// Includes

#include "engine/engine.hpp"
#include "graphics/window.h"

namespace experiment
{
  void brownian(std :: ofstream & oeb, std :: ofstream & otb, std :: uniform_real_distribution<double> & unif, std :: default_random_engine & re);

  void disequilibrium(std :: ofstream & oeb, std :: ofstream & otb, std :: uniform_real_distribution<double> & unif, std :: default_random_engine & re);
};

#endif
