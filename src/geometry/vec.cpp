#include "vec.h"

// Constructors

vec :: vec()
{
}

vec :: vec(double x, double y): x(x), y(y)
{
}

vec :: vec(int fold)
{
  this->x = (fold & horizontal) == direct ? 0. : ((fold & horizontal) == right ? 1. : -1);
  this->y = (fold & vertical) == direct ? 0. : ((fold & vertical) == up ? 1. : -1);
}

// Methods

vec vec :: normalize() const
{
  return (*this) / !(*this);
}

// Operators

vec vec :: operator - () const
{
  return vec(-x, -y);
}

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
  return (*this);
}

vec vec :: operator % (const double & angle) const
{
  double sin_angle = sin(angle);
  double cos_angle = cos(angle);
  return vec(cos_angle * this->x - sin_angle * this->y, sin_angle * this->x + cos_angle * this->y);
}

vec & vec :: operator %= (const double & angle)
{
  (*this) = (*this) % angle;
  return (*this);
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

bool vec :: operator == (const vec & rho) const
{
  return this->x == rho.x && this->y == rho.y;
}

// External Operators

vec operator * (const double & lho, const vec & rho)
{
  return rho * lho;
}

// Standard Output

std :: ostream & operator << (std :: ostream & out, const vec & v)
{
  return out << "(" << v.x << ", " << v.y << ")";
}
