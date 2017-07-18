## Class `vec`

### Overview

Class `vec` implements an object-oriented interface to two-dimensional vectors of `double`, offering operators for all its elementary operations.

### Example usage

```c++
#include <iostream>

#include "geometry/vec.h"

int main()
{
  vec my_vec(10.5, 5.2);
  std :: cout << my_vec << std :: endl; // Prints (10.5, 5.2)

  my_vec.x -= 5.5;
  my_vec.y = 15;
  std :: cout << my_vec << std :: endl; // Prints (5, 15)

  std :: cout << my_vec.normalize() << endl; // Prints (0.25, 0.75)

  // Etc
}
```

### Interface

#### Constructors

 * `vec()`
    builds a vector with unitialized components.

 * `vec(const double &, const double &)`
    builds a vector with the two given components.

 * `vec(int)`
    given a `fold` variable (see below for nested `enum fold`), builds a vector that represents the corresponding fold, represented by the integer.

#### Methods

 * `vec normalize() const`
    returns the vector normalized.

#### Operators

 * `vec operator - () const`
    returns the reverse of the vector.

 * `vec operator + (const vec &) const`
    returns the sum of the two vectors.

 * `vec & operator += (const vec &)`
    sums the right hand operand to the left hand operand.

 * `vec operator - (const vec &) const`
    returns the difference of the two vectors.

 * `vec & operator -= (const vec &)`
    subtracts the right hand operand to the left hand operand.

 * `vec operator * (const double &) const`
    returns the vector multiplied by the scalar. (A corrispective external operator `vec operator * (const double &, const vec &)` is provided)

 * `vec & operator *= (const double &)`
    multiplies the vector for the given double.

 * `vec operator / (const double &) const`
    returns the vector quotient.

 * `vec & operator =/ (const double &)`
    divide the vector for the given double.

 * `vec operator % (const double &) const`
    returns the vector rotated for a given ammount of radiants.

 * `vec & operator %= (const double &)`
    rotates the vector for a given ammount of radiants.

 * `double operator ^ (const vec &) const`
    returns the cross product.

 * `double operator * (const vec &) const`
    returns the scalar product.

 * `double operator ~ () const`
    returns the squared module.

 * `double operator ! () const`
    returns the module.

 * `bool operator == (const vec &) const`
    equality operator.

 * `std :: ostream & operator << (std :: ostream &, const vec &)`
    standard output.

### Nested enum `fold`

#### Declaration

```c++
enum fold {direct = 0x0, left = 0x1, right = 0x2, up = 0x4, down = 0x8, horizontal = 0x3, vertical = 0xc};
```

#### Overview

Enum `fold` is a bitmask-wise object for representing the possible combination of translations inside the continuos space.
It's made of six elements:
 * 2 horizontal translations
    left, right
 * 2 vertical translations
    up, down
 * 1 null translation
    direct
 * 2 bitmask-wise extracting elements
    horizontal, vertical

It's possible to assemble one horizontal and one vertical translation into a single integer representation with the operator `||`.
It's also possible to check the horizontal or the vertical component of the integer representation with one extractiong element and the operator `&&`

#### Example usage of `fold`

```c++
int horizontal_fold = vec :: left;
int vertical_fold = vec :: up;
int my_fold = vec :: down || vec :: right;
int no_fold = vec :: direct;

std :: cout << vec(horizontal_fold) << std :: endl; \\ Prints (-1, 0)
std :: cout << vec(vertical_fold) << std :: endl; \\ Prints (0, 1)
std :: cout << vec(my_fold) << std :: endl; \\ Prints (1, -1)
std :: cout << vec(no_fold) << std :: endl; \\ Prints (0, 0)
std :: cout << vec(my_fold && vec :: vertical) << std :: endl; \\ Prints (0, -1)
```

...
