## Class `bumper`

### Overview

Class `bumper` is an object-oriented representation of a spherical immovable obstacle in a 2-dimensional space.

### Interface

#### Constructors

  * `bumper()`
    builds an uninitialized bumper.

  * `bumper(const vec & position, const double & radius)`
    builds a bumper with the given values.

#### Public members

  * `grid :: mark`
    position of the molecule inside the engine grid.

#### Getters

  * `const vec & position() const`
  * `const double & radius() const`
