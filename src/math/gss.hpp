#ifndef __nobb__math__gss__hpp
#define __nobb__math__gss__hpp

#include "gss.h"

// Static methods

template <typename type, typename std :: enable_if <gss :: valid <type> :: value> :: type *> double gss :: min(const type & f, double a, double b)
{
  static const double ratio = (sqrt(5.) + 1.) / 2.;

  double c = b - (b - a) / ratio;
  double d = a + (b - a) / ratio;

  for(unsigned int i = 0; fabs(c - d) > std :: numeric_limits <double> :: epsilon() && i < rounds; i++)
  {
    if(f(c) < f(d))
      b = d;
    else
      a = c;

    c = b - (b - a) / ratio;
    d = a + (b - a) / ratio;
  }

  return (b + a) / 2.;
}

template <typename type, typename std :: enable_if <gss :: valid <type> :: value> :: type *> double gss :: max(const type & f, double a, double b)
{
  static const double ratio = (sqrt(5.) + 1.) / 2.;

  double c = b - (b - a) / ratio;
  double d = a + (b - a) / ratio;

  for(unsigned int i = 0; fabs(c - d) > std :: numeric_limits <double> :: epsilon() && i < rounds; i++)
  {
    if(f(c) > f(d))
      b = d;
    else
      a = c;

    c = b - (b - a) / ratio;
    d = a + (b - a) / ratio;
  }

  return (b + a) / 2.;
}

#endif
