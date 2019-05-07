## Class `report` (event/reports/bumper.h)

### Overview

Polymorphic class `report` gives the user a complete set of tools for the analyisis of an event and its elements in a convenient form. It's also a fundamental element required for building a valid lambda function that can be correctly wrapped by the `callback` class (see **callback** folder documentation) into a valid subscription for the `dispatcher`.

This `report` is fully specialized for `events :: bumper`.

### Interface

Since the interface is based on many public nested classes, we report directly the main constructor and the nested getters in their most convenient form.

#### Constructor

  * `report(const events :: bumper & event)`

    builds the report and all the public nested classes.

#### Getters (and nested getters in convenient form)

**Getters for general informations**

  * `const double & time() const`

    time of the event.

  * `const double & module() const`

    module of the collision's impulse.

**Getters for bumper**

  * `const vec & position() const`

    position of bumper.

  * `const double & radius() const`

    radius of bumper.

**Getters for molecule**

  * `const vec & velocity.before() const`

    velocity of molecule before the event.

  * `const vec & velocity.after() const`

    velocity of molecule after the event.

  * `const vec velocity.delta() const`

    variation of velocity of molecule.

  * `const vec & momentum.before() const`

    momentum of molecule before the event.

  * `const vec & momentum.after() const`

    momentum of molecule after the event.

  * `const vec momentum.delta() const`

    variation of momentum of molecule.

  * `const double & angular_velocity.before() const`

    angular velocity of molecule before the event.

  * `const double & angular_velocity.after() const`

    angular velocity of molecule after the event.

  * `const double angular_velocity.delta() const`

    variation of angular velocity of molecule.

  * `const double & angular_momentum.before() const`

    angular momentum of molecule before the event.

  * `const double & angular_momentum.after() const`

    angular momentum of molecule after the event.

  * `const double angular_momentum.delta() const`

    variation of angular momentum of molecule.

  * `const double energy.before() const`

    energy of molecule before the event.

  * `const double energy.after() const`

    energy of molecule after the event.

  * `const double energy.delta() const`

    variation of energy of molecule.

  * `const size_t & id() const`

    id of molecule.

  * `const size_t & atom() const`

    id of molecule's atom involved in the collision.

  * `const vec & position() const`

    position of molecule at the collision moment.

  * `const double & orientation() const`

    orientation of molecule at the orientation moment.

  * `const double & mass() const`

    mass of molecule.
