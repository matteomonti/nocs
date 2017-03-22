#include "vec.h"

// Constructors

vec :: vec()
{
}

vec :: vec(double x, double y): x(x), y(y)
{
}

// Operators

vec vec :: operator + (const vec & rho) const
{
  return vec(x + rho.x, y + rho.y);
}

vec & vec :: operator += (const vec & rho)
{
  x += rho.x;
  y += rho.y;
  return *this;
}

vec vec :: operator - (const vec & rho) const
{
  return vec(x - rho.x, y - rho.y);
}

vec & vec :: operator -= (const vec & rho)
{
  x -= rho.x;
  y -= rho.y;
  return *this;
}

vec vec :: operator * (const double & rho) const
{
  return vec(x * rho, y * rho);
}

vec & vec :: operator *= (const double & rho)
{
  x *= rho;
  y *= rho;
  return *this;
}

vec vec :: operator / (const double & rho) const
{
  return vec(x / rho, y / rho);
}

vec & vec :: operator /= (const double & rho)
{
  x /= rho;
  y /= rho;
}

double vec :: operator ^ (const vec & rho) const
{
  return (x * rho.y - y * rho.x);
}

double vec :: operator * (const vec & rho) const
{
  return (x * rho.x + y * rho.y);
}

double vec :: operator ~ () const
{
  return (x * x + y * y);
}

double vec :: operator ! () const
{
  return sqrt(~*this);
}

// External Operators

vec operator * (const double & lho, const vec & rho)
{
  return rho * lho;
}

// Standard Output

std :: ostream & operator << (std :: ostream & out, const vec & v)
{
  return out << "(" << v.x << ", " << v.y << ")" << std :: endl;
}
