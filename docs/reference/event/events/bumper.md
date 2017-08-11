## Class `bumper` (event/events/bumper.h)

### Overview

Class `bumper` represents the collision of a molecule with a bumper as an object-oriented event.

### Interface

#### Constructor

  * `bumper(:: molecule & molecule, const int & fold, :: bumper & bumper)`
    builds a collision event with the given elements and verifies whether the collision will happen or not. (fold indicates the standard translation to be considered for `molecule`, following the standard given in **vec.md**)

#### Getters

  * `bool happens() const`
    returns whether the event will happen or not.

  * `double time() const`
    returns when the event will happen.

  * `const :: molecule & molecule() const`
    returns the molecule involved in the collision.

#### Public Methods

  * `virtual bool current()`
    returns whether the involved elements are in the correct version or not.

  * `virtual vool resolve()`
    executes the event with its dynamical consequences.

  * `virtual void each(engine * engine, void (engine :: *callback)(molecule &, const size_t &))`
    given the working engine and a method of the engine that takes as argument a `molecule &` and a `const size_t &`, executes the given method to each molecule involved in the event. (In this case, one molecule is involved)

  * `virtual void callback(dispatcher & dispatcher)`
    given the engine's main dispatcher, executes the dispatcher's trigger for the event, which will execute the corrispondent requested reports, if any.

#### Standard Output

  * `friend std :: ostream & operator << (std :: ostream &, const event &)`
    executes the function `std :: ostream & print(std :: ostream &) const`.
