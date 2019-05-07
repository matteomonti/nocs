## Class `resetter`

### Overview

Class `resetter` is a component of `engine` that allows the user to reset the energy of any molecule or group of molecules into any desired value, maintaining all the internal proportions.

### Service nested classes

#### `class energy`

Actual part of the class that implements the energy reset system.

**Constructor**

  * `energy(engine & engine)`

**Methods**

  * `void id(const size_t & id, const double & energy)`

    resets the energy of the molecule with given id to the given energy value.

  * `void tag(const unit8_t & tag, const double & energy)`

    resets the energy of all the molecules with the given tag to the given energy value.

  * `void all(const double & energy)`

    resets the energy of all the molecules to the given energy value.

### Interface

#### Public members

  * `energy energy`

    by placing the service nested class `energy` as a member, it is possible for the user to request resets in a nice format. (e.g. `my_engine.reset.energy.tag(my_tag, 1);` where `my_engine` is an `engine` that has a `resetter` named `reset` and `energy` is actually contained into `reset`)
