// Forward declarations

struct vec;

#if !defined(__forward__) && !defined(__nobb__geometry__vec__h)
#define __nobb__geometry__vec__h

// Libraries

#include <iostream>
#include <cmath>

struct vec
{
  // Nested enums

  enum fold {direct = 0x0, left = 0x1, right = 0x2, up = 0x4, down = 0x8, horizontal = 0x3, vertical = 0xc};

  // Members

  double x, y;

  // Constructors

  vec();
  vec(double, double);
  vec(int);

  // Methods

  vec normalize() const;

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

  vec operator % (const double &) const;  // Rotation operator (radiants)
  vec & operator %= (const double &);

  double operator ^ (const vec &) const;  // Cross Product
  double operator * (const vec &) const;  // Scalar Product

  double operator ~ () const; // Squared Module
  double operator ! () const; // Module

  bool operator == (const vec &) const;
};

// External Operators

vec operator * (const double &, const vec &);

// Standard Output

std :: ostream & operator << (std :: ostream &, const vec &);

#endif
