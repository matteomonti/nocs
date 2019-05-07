## Class `molecule` (event/events/molecule.h)

### Overview

Class `molecule` represents the collision of two molecules as an object-oriented event.

### Interface

#### Constructor

  * `molecule(:: molecule & molecule_alpha, const int & fold, :: molecule & molecule_beta, const double & elasticity = 1.)`

    builds a collision event with the given elements and verifies whether the collision will happen or not. If it happens, it will be a collision with the given elasticity. (fold indicates the standard translation to be considered for `molecule_alpha`, following the standard given in **vec.md**)

#### Getters

  * `bool happens() const`

    returns whether the event will happen or not.

  * `double time() const`

    returns when the event will happen.

  * `const :: molecule & alpha() const`

    returns the first molecule involved in the collision.

  * `const :: molecule & beta() const`

    returns the second molecule involved in the collision.

#### Public Methods

  * `virtual bool current()`

    returns whether the involved elements are in the correct version or not.

  * `virtual vool resolve()`

    executes the event with its dynamical consequences.

  * `virtual void each(engine * engine, void (engine :: *callback)(molecule &, const size_t &))`

    given the working engine and a method of the engine that takes as argument a `molecule &` and a `const size_t &`, executes the given method to each molecule involved in the event. (In this case, two molecules are involved)

  * `virtual void callback(dispatcher & dispatcher)`

    given the engine's main dispatcher, executes the dispatcher's trigger for the event, which will execute the corrispondent requested reports, if any.

#### Standard Output

  * `friend std :: ostream & operator << (std :: ostream &, const event &)`

    executes the function `std :: ostream & print(std :: ostream &) const`.
