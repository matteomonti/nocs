#include "bumper.h"
#include "event/events/bumper.h"

// Public nested classes

// velocity

// Constructors

report <events :: bumper> :: velocity :: velocity(const events :: bumper & event) : _event(event)
{
}

// Getters

const vec & report <events :: bumper> :: velocity :: before() const
{
  return this->_event.v;
}

const vec & report <events :: bumper> :: velocity :: after() const
{
  return this->_event._molecule.molecule->velocity();
}

const vec report <events :: bumper> :: velocity :: delta () const
{
  return this->after() - this->before();
}

// momentum

// Constructors

report <events :: bumper> :: momentum :: momentum(const events :: bumper & event) : _event(event)
{
}

// Getters

const vec & report <events :: bumper> :: momentum :: before() const
{
  return this->_event.p;
}

const vec report <events :: bumper> :: momentum :: after() const
{
  return this->_event._molecule.molecule->velocity() * this->_event._molecule.molecule->mass();
}

const vec report <events :: bumper> :: momentum :: delta() const
{
  return this->after() - this->before();
}

// angular_velocity

// Constructors

report <events :: bumper> :: angular_velocity :: angular_velocity(const events :: bumper & event) : _event(event)
{
}

// Getters

const double & report <events :: bumper> :: angular_velocity :: before() const
{
  return this->_event.av;
}

const double & report <events :: bumper> :: angular_velocity :: after() const
{
  return this->_event._molecule.molecule->angular_velocity();
}

const double report <events :: bumper> :: angular_velocity :: delta() const
{
  return this->after() - this->before();
}

// angular_momentum

// Constructors

report <events :: bumper> :: angular_momentum :: angular_momentum(const events :: bumper & event) : _event(event)
{
}

// Getters

const double & report <events :: bumper> :: angular_momentum :: before() const
{
  return this->_event.l;
}

const double report <events :: bumper> :: angular_momentum :: after() const
{
  return this->_event._molecule.molecule->angular_velocity() * this->_event._molecule.molecule->inertia_moment();
}

const double report <events :: bumper> :: angular_momentum :: delta() const
{
  return this->after() - this->before();
}

// energy

// Constructors

report <events :: bumper> :: energy :: energy(const events :: bumper & event) : _event(event)
{
}

// Getters

const double report <events :: bumper> :: energy :: before() const
{
  return 0.5 * (~this->_event.v * this->_event._molecule.molecule->mass() + this->_event.av * this->_event.av * this->_event._molecule.molecule->inertia_moment());
}

const double report <events :: bumper> :: energy :: after() const
{
  return this->_event._molecule.molecule->energy();
}

const double report <events :: bumper> :: energy :: delta() const
{
  return this->after() - this->before();
}

// bumper

// Constructors

report <events :: bumper> :: bumper :: bumper(const events :: bumper & event) : _event(event)
{
}

// Methods

const vec & report <events :: bumper> :: bumper :: position() const
{
  return this->_event._bumper->position();
}

const double & report <events :: bumper> :: bumper :: radius() const
{
  return this->_event._bumper->radius();
}

// Constructors

report <events :: bumper> :: report(const events :: bumper & event) : _event(event), velocity(event), momentum(event), angular_velocity(event), angular_momentum(event), energy(event), bumper(event)
{
}

// Getters

const size_t & report <events :: bumper> :: id() const
{
  return this->_event._molecule.molecule->tag.id();
}

const size_t & report <events :: bumper> :: atom() const
{
  return this->_event._molecule.atom;
}

const vec & report <events :: bumper> :: position() const
{
  return this->_event._molecule.molecule->position();
}

const double & report <events :: bumper> :: orientation() const
{
  return this->_event._molecule.molecule->orientation();
}

const double & report <events :: bumper> :: mass() const
{
  return this->_event._molecule.molecule->mass();
}

const double & report <events :: bumper> :: time() const
{
  return this->_event._time;
}

const double & report <events :: bumper> :: module() const
{
  return this->_event.module;
}
