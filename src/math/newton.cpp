#include "newton.h"

namespace newton
{
  double quadratic(const double & a, const double & b, const double & c, double x)
  {
    if(b * b - 4. * a * c < epsilon)
      return NAN;

    for(unsigned int i = 0; i < rounds; i++)
    {
      double y = (a * x * x + b * x + c);

      if(fabs(y) < epsilon)
        return x;

      x = x -  y / (2. * a * x + b);
    }

    return x;
  }
}
