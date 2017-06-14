#include "molecule.h"
#include "event/events/molecule.h"

namespace reports
{
  // Public nested classes

  // alpha

  // Public nested classes

  // alpha :: velocity

  // Constructors

  molecule :: alpha :: velocity :: velocity(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const vec & molecule :: alpha :: velocity :: before() const
  {
    return this->_event.v1;
  }

  const vec & molecule :: alpha :: velocity :: after() const
  {
    return this->_event._alpha.molecule->velocity();
  }

  const vec molecule :: alpha :: velocity :: delta() const
  {
    return this->after() - this->before();
  }

  // alpha :: momentum

  // Constructors

  molecule :: alpha :: momentum :: momentum(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const vec & molecule :: alpha :: momentum :: before() const
  {
    return this->_event.p1;
  }

  const vec molecule :: alpha :: momentum :: after() const
  {
    return this->_event._alpha.molecule->velocity() * this->_event._alpha.molecule->mass();
  }

  const vec molecule :: alpha :: momentum :: delta() const
  {
    return this->after() - this->before();
  }

  // alpha :: angular_velocity

  // Constructors

  molecule :: alpha :: angular_velocity :: angular_velocity(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const double & molecule :: alpha :: angular_velocity :: before() const
  {
    return this->_event.av1;
  }

  const double & molecule :: alpha :: angular_velocity :: after() const
  {
    return this->_event._alpha.molecule->angular_velocity();
  }

  const double molecule :: alpha :: angular_velocity :: delta() const
  {
    return this->after() - this->before();
  }

  // alpha :: angular_momentum

  // Constructors

  molecule :: alpha :: angular_momentum :: angular_momentum(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const double & molecule :: alpha :: angular_momentum :: before() const
  {
    return this->_event.l1;
  }

  const double molecule :: alpha :: angular_momentum :: after() const
  {
    return this->_event._alpha.molecule->angular_velocity() * this->_event._alpha.molecule->mass();
  }

  const double molecule :: alpha :: angular_momentum :: delta() const
  {
    return this->after() - this->before();
  }

  // alpha :: energy

  // Constructors

  molecule :: alpha :: energy :: energy(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const double molecule :: alpha :: energy :: before() const
  {
    return 0.5 * ( (~this->_event.v1) * this->_event._alpha.molecule->mass() + this->_event.av1 * this->_event.av1 * this->_event._alpha.molecule->inertia_moment());
  }

  const double molecule :: alpha :: energy :: after() const
  {
    return this->_event._alpha.molecule->energy();
  }

  const double molecule :: alpha :: energy :: delta() const
  {
    return this->after() - this->before();
  }

  // Constructors

  molecule :: alpha :: alpha(const events :: molecule & event) : _event(event), velocity(event), momentum(event), angular_velocity(event), angular_momentum(event), energy(event)
  {}

  // Getters

  const size_t & molecule :: alpha :: id() const
  {
    return this->_event._alpha.molecule->tag.id();
  }

  const size_t & molecule :: alpha :: atom() const
  {
    return this->_event._alpha.atom;
  }

  const vec & molecule :: alpha :: position() const
  {
    return this->_event._alpha.molecule->position();
  }

  const double & molecule :: alpha :: orientation() const
  {
    return this->_event._alpha.molecule->orientation();
  }

  const double & molecule :: alpha :: mass() const
  {
    return this->_event._alpha.molecule->mass();
  }

  // beta

  // Public nested classes

  // beta :: velocity

  // Constructors

  molecule :: beta :: velocity :: velocity(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const vec & molecule :: beta :: velocity :: before() const
  {
    return this->_event.v2;
  }

  const vec & molecule :: beta :: velocity :: after() const
  {
    return this->_event._beta.molecule->velocity();
  }

  const vec molecule :: beta :: velocity :: delta() const
  {
    return this->after() - this->before();
  }

  // beta :: momentum

  // Constructors

  molecule :: beta :: momentum :: momentum(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const vec & molecule :: beta :: momentum :: before() const
  {
    return this->_event.p2;
  }

  const vec molecule :: beta :: momentum :: after() const
  {
    return this->_event._beta.molecule->velocity() * this->_event._beta.molecule->mass();
  }

  const vec molecule :: beta :: momentum :: delta() const
  {
    return this->after() - this->before();
  }

  // beta :: angular_velocity

  // Constructors

  molecule :: beta :: angular_velocity :: angular_velocity(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const double & molecule :: beta :: angular_velocity :: before() const
  {
    return this->_event.av2;
  }

  const double & molecule :: beta :: angular_velocity :: after() const
  {
    return this->_event._beta.molecule->angular_velocity();
  }

  const double molecule :: beta :: angular_velocity :: delta() const
  {
    return this->after() - this->before();
  }

  // beta :: angular_momentum

  // Constructors

  molecule :: beta :: angular_momentum :: angular_momentum(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const double & molecule :: beta :: angular_momentum :: before() const
  {
    return this->_event.l2;
  }

  const double molecule :: beta :: angular_momentum :: after() const
  {
    return this->_event._beta.molecule->angular_velocity() * this->_event._beta.molecule->mass();
  }

  const double molecule :: beta :: angular_momentum :: delta() const
  {
    return this->after() - this->before();
  }

  // beta :: energy

  // Constructors

  molecule :: beta :: energy :: energy(const events :: molecule & event) : _event(event)
  {}

  // Getters

  const double molecule :: beta :: energy :: before() const
  {
    return 0.5 * ((~this->_event.v2) * this->_event._beta.molecule->mass() + this->_event.av2 * this->_event.av2 * this->_event._beta.molecule->inertia_moment());
  }

  const double molecule :: beta :: energy :: after() const
  {
    return this->_event._beta.molecule->energy();
  }

  const double molecule :: beta :: energy :: delta() const
  {
    return this->after() - this->before();
  }

  // Constructors

  molecule :: beta :: beta(const events :: molecule & event) : _event(event), velocity(event), momentum(event), angular_velocity(event), angular_momentum(event), energy(event)
  {}

  // Getters

  const size_t & molecule :: beta :: id() const
  {
    return this->_event._beta.molecule->tag.id();
  }

  const size_t & molecule :: beta :: atom() const
  {
    return this->_event._beta.atom;
  }

  const vec & molecule :: beta :: position() const
  {
    return this->_event._beta.molecule->position();
  }

  const double & molecule :: beta :: orientation() const
  {
    return this->_event._beta.molecule->orientation();
  }

  const double & molecule :: beta :: mass() const
  {
    return this->_event._beta.molecule->mass();
  }

  // Constructors

  molecule :: molecule(const events :: molecule & event) : _event(event), alpha(event), beta(event)
  {}

  // Getters

  const double & molecule :: time() const
  {
    return this->_event._time;
  }

  const double & molecule :: module() const
  {
    return this->_event.module;
  }
};
