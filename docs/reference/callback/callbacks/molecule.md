## Class `callback` (callback/callbacks/molecule.h)

### Overview

Class `callback` is a polymorphic wrapper for lambda functions that gives them an interface in order to interact correctly with the `dispatcher`.
This `callback` is completely specialized for `events :: molecule` and can be built only with lambdas that take as argument a `report <events :: molecule>` object.

### Interface

#### Constructor

  * `callback(const lambda & function)`

    builds the callback with the given function.

#### Methods

  * `void trigger(const events :: molecule & event)`

    given an event of the correct kind, sets off the lambda function by giving it as argument a `report` about the given event. 
