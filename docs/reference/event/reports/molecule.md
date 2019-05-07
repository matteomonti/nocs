## Class `report` (event/reports/molecule.h)

### Overview

Polymorphic class `report` gives the user a complete set of tools for the analyisis of an event and its elements in a convenient form. It's also a fundamental element required for building a valid lambda function that can be correctly wrapped by the `callback` class (see **callback** folder documentation) into a valid subscription for the `dispatcher`.

This `report` is fully specialized for `events :: molecule`.

### Interface

Since the interface is based on many public nested classes, we report directly the main constructor and the nested getters in their most convenient form.

#### Constructor

  * `report(const events :: molecule & event)`

    builds the report and all the public nested classes.

#### Getters (and nested getters in convenient form)

**Getters for general informations**

  * `const double & time() const`

    time of the event.

  * `const double & module() const`

    module of the collision's impulse.

**Getters for alpha molecule**

  * `const vec & alpha.velocity.before() const`

    velocity of alpha molecule before the event.

  * `const vec & alpha.velocity.after() const`

    velocity of alpha molecule after the event.

  * `const vec alpha.velocity.delta() const`

    variation of velocity of alpha molecule.

  * `const vec & alpha.momentum.before() const`

    momentum of alpha molecule before the event.

  * `const vec & alpha.momentum.after() const`

    momentum of alpha molecule after the event.

  * `const vec alpha.momentum.delta() const`

    variation of momentum of alpha molecule.

  * `const double & alpha.angular_velocity.before() const`

    angular velocity of alpha molecule before the event.

  * `const double & alpha.angular_velocity.after() const`

    angular velocity of alpha molecule after the event.

  * `const double alpha.angular_velocity.delta() const`

    variation of angular velocity of alpha molecule.

  * `const double & alpha.angular_momentum.before() const`

    angular momentum of alpha molecule before the event.

  * `const double & alpha.angular_momentum.after() const`

    angular momentum of alpha molecule after the event.

  * `const double alpha.angular_momentum.delta() const`

    variation of angular momentum of alpha molecule.

  * `const double alpha.energy.before() const`

    energy of alpha molecule before the event.

  * `const double alpha.energy.after() const`

    energy of alpha molecule after the event.

  * `const double alpha.energy.delta() const`

    variation of energy of alpha molecule.

  * `const size_t & alpha.id() const`

    id of alpha molecule.

  * `const size_t & alpha.atom() const`

    id of alpha molecule's atom involved in the collision.

  * `const vec & alpha.position() const`

    position of alpha molecule at the collision moment.

  * `const double & alpha.orientation() const`

    orientation of alpha molecule at the orientation moment.

  * `const double & alpha.mass() const`

    mass of alpha molecule.

**Getters for beta molecule**

  * `const vec & beta.velocity.before() const`

    velocity of beta molecule before the event.

  * `const vec & beta.velocity.after() const`

    velocity of beta molecule after the event.

  * `const vec beta.velocity.delta() const`

    variation of velocity of beta molecule.

  * `const vec & beta.momentum.before() const`

    momentum of beta molecule before the event.

  * `const vec & beta.momentum.after() const`

    momentum of beta molecule after the event.

  * `const vec beta.momentum.delta() const`

    variation of momentum of beta molecule.

  * `const double & beta.angular_velocity.before() const`

    angular velocity of beta molecule before the event.

  * `const double & beta.angular_velocity.after() const`

    angular velocity of beta molecule after the event.

  * `const double beta.angular_velocity.delta() const`

    variation of angular velocity of beta molecule.

  * `const double & beta.angular_momentum.before() const`

    angular momentum of beta molecule before the event.

  * `const double & beta.angular_momentum.after() const`

    angular momentum of beta molecule after the event.

  * `const double beta.angular_momentum.delta() const`

    variation of angular momentum of beta molecule.

  * `const double beta.energy.before() const`

    energy of beta molecule before the event.

  * `const double beta.energy.after() const`

    energy of beta molecule after the event.

  * `const double beta.energy.delta() const`

    variation of energy of beta molecule.

  * `const size_t & beta.id() const`

    id of beta molecule.

  * `const size_t & beta.atom() const`

    id of beta molecule's atom involved in the collision.

  * `const vec & beta.position() const`

    position of beta molecule at the collision moment.

  * `const double & beta.orientation() const`

    orientation of beta molecule at the orientation moment.

  * `const double & beta.mass() const`

    mass of beta molecule.
