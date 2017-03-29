#if !defined(__forward__) && !defined(__nobb__math__newton__h)
#define __nobb__math__newton__h

// Libraries

#include <cmath>
#include <limits>

// Macros

#define NaN (0./0.)

namespace newton
{
  constexpr double epsilon = 5. * std :: numeric_limits <double> :: epsilon();
  constexpr unsigned int rounds = 50;

  double quadratic(const double &, const double &, const double &, double = 0);
};

#endif
