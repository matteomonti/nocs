## Class `molecule`

### Overview

Class `molecule` is the object-oriented representation of a generic molecule of arbitrary shape and mass in dynamic motion inside a 2-dimensional space.

### Interface

#### Public members

  * `grid :: mark`
    position of the molecule inside the engine grid.

  * `engine :: tag`
    tags of the molecule in the engine context.

#### Constructors

 * `molecule()`
    default constructor.
 * `molecule(const std :: vector<atom> & atoms, const vec & position = vec(0, 0), const vec & = velocity vec(0, 0), const double &  orientation = 0, const double angular_velocity & = 0)`
    builds a molecule with the given parameters and the given vector of `atoms`.
    **REMARK: atoms' position is absolute and is automatically altered in order to have the center of mass of the molecule at the given position.**

#### Getters

  * `const size_t & size() const;`
  * `const vec & position() const;`
  * `const vec & velocity() const;`
  * `const double & orientation() const;`
  * `const double & angular_velocity() const;`
  * `const double & radius() const;`
  * `const double & mass() const;`
  * `const double & inertia_moment() const;`
  * `const double & time() const;`
  * `const int32_t & version() const;`

  * `const double energy() const;`

#### Methods

  * `void integrate(const double & time)`
    integrates the motion of the molecule at a given time.
    **REMARK: does nothing if the given time is less or equal of the starting time of the molecule (a molecule can't go backwards in time).**

  * `void impulse(const vec & point_of_application, const vec & impulse)`
    given an impulse and a point of application on the molecule, computes the effects of the impulse and updates molecule's velocity and angular_velocity.

  * `void teleport(const vec :: fold & fold)`
    given a `fold` enum (see `vec` reference for more details), translates the molecule.

  * `void scale_energy(const double &)`
    given a new amount of energy, rescales the velocity and the angular_velocity of the molecule accordingly.

  * `void disable()`
    activates the `disabled` tag of the molecule and, therefore, the molecule stops interacting whith other objects inside the engine and will be removed shortly after by the garbage collector.

#### Operators

  * `const atom & operator [] (const size_t &) const`
    access an atom that constitutes the molecule.

  * `molecule & operator ++ ()`
    increments molecule's version.

  * `molecule operator ++ (int)`
    increments molecule's version.
