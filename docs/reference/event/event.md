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
    given the working engine and a method of the engine that takes as argument a `molecule &` and a `const size_t &`, executes the given method to each molecule involved in the event.

  * `virtual void callback(dispatcher & dispatcher)`
    given the engine's main dispatcher, executes the dispatcher's trigger for the event, which will execute the corrispondent requested reports, if any.

#### Standard Output

  * `friend std :: ostream & operator << (std :: ostream &, const event &)`
    executes the function `virtual std :: ostream & print(std :: ostream &) const`. 
