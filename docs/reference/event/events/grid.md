## Class `grid` (event/events/grid.h)

### Overview

Class `grid` represents a molecule changing region inside the engine's grid as an object-oriented event. It's also the event that guarantees space continuity by performing translations on the molecules when it's required.

### Interface

#### Constructor

  * `grid(:: molecule & molecule, :: grid & grid);`

    builds an event with the given elements and computates when the given molecule, maintaining its uniform motion, will switch region.

#### Getters

  * `bool happens() const`

    returns whether the event will happen or not.

  * `double time() const`

    returns when the event will happen.

#### Public Methods

  * `virtual bool current()`

    returns whether the involved elements are in the correct version or not.

  * `virtual vool resolve()`

    executes the event with its dynamical consequences.

  * `virtual void each(engine * engine, void (engine :: *callback)(molecule &, const size_t &))`

    given the working engine and a method of the engine that takes as argument a `molecule &` and a `const size_t &`, executes the given method to each molecule involved in the event. (In this case, one molecule)

#### Standard Output

  * `friend std :: ostream & operator << (std :: ostream &, const event &)`

    executes the function `std :: ostream & print(std :: ostream &) const`.
