## Class `event`

### Overview

Class `event` is the abstract base class for the engine's event system.

### Interface

#### Getters

  * `bool happens() const`
    returns whether the event will happen or not.

  * `double time() const`
    returns when the event will happen.

#### Public Methods

  * `virtual bool current() = 0`
    returns whether the involved elements are in the correct version or not.

  * `virtual vool resolve() = 0`
    executes the event with its dynamical consequences.

  * `virtual void each(engine * engine, void (engine :: *callback)(molecule &, const size_t &)) = 0`

  * ``

#### Standard Output

  * ``
