// Forward declarations

struct vec;

#if !defined(__forward__) && !defined(__nobb__geometry__vec__h)
#define __nobb__geometry__vec__h

// Libraries

#include <iostream>
#include <cmath>

struct vec
{
  // Members

  double x, y;

  // Constructors

  vec();
  vec(double, double);

  // Operators

  vec operator - () const;

  vec   operator +  (const vec &) const;
  vec & operator += (const vec &);

  vec   operator -  (const vec &) const;
  vec & operator -= (const vec &);

  vec operator *  (const double &) const;
  vec & operator *=  (const double &);

  vec operator /  (const double &) const;
  vec & operator /=  (const double &);

  double operator ^ (const vec &) const;  // Cross Product
  double operator * (const vec &) const;  // Scalar Product

  double operator ~ () const; // Squared Module
  double operator ! () const; // Module
};

// External Operators

vec operator * (const double &, const vec &);

// Standard Output

std :: ostream & operator << (std :: ostream &, const vec &);

#endif
