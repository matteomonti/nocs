#include "molecule.h"
#include "event/events/molecule.h"

// Public nested classes

// alpha

// Public nested classes

// alpha :: velocity

// Constructors

report <events :: molecule> :: alpha :: velocity :: velocity(const events :: molecule & event) : _event(event)
{}

// Getters

const vec & report <events :: molecule> :: alpha :: velocity :: before() const
{
  return this->_event.v1;
}

const vec & report <events :: molecule> :: alpha :: velocity :: after() const
{
  return this->_event._alpha.molecule->velocity();
}

vec report <events :: molecule> :: alpha :: velocity :: delta() const
{
  return this->after() - this->before();
}

// alpha :: momentum

// Constructors

report <events :: molecule> :: alpha :: momentum :: momentum(const events :: molecule & event) : _event(event)
{}

// Getters

const vec & report <events :: molecule> :: alpha :: momentum :: before() const
{
  return this->_event.p1;
}

vec report <events :: molecule> :: alpha :: momentum :: after() const
{
  return this->_event._alpha.molecule->velocity() * this->_event._alpha.molecule->mass();
}

vec report <events :: molecule> :: alpha :: momentum :: delta() const
{
  return this->after() - this->before();
}

// alpha :: angular_velocity

// Constructors

report <events :: molecule> :: alpha :: angular_velocity :: angular_velocity(const events :: molecule & event) : _event(event)
{}

// Getters

const double & report <events :: molecule> :: alpha :: angular_velocity :: before() const
{
  return this->_event.av1;
}

const double & report <events :: molecule> :: alpha :: angular_velocity :: after() const
{
  return this->_event._alpha.molecule->angular_velocity();
}

double report <events :: molecule> :: alpha :: angular_velocity :: delta() const
{
  return this->after() - this->before();
}

// alpha :: angular_momentum

// Constructors

report <events :: molecule> :: alpha :: angular_momentum :: angular_momentum(const events :: molecule & event) : _event(event)
{}

// Getters

const double & report <events :: molecule> :: alpha :: angular_momentum :: before() const
{
  return this->_event.l1;
}

double report <events :: molecule> :: alpha :: angular_momentum :: after() const
{
  return this->_event._alpha.molecule->angular_velocity() * this->_event._alpha.molecule->mass();
}

double report <events :: molecule> :: alpha :: angular_momentum :: delta() const
{
  return this->after() - this->before();
}

// alpha :: energy

// Constructors

report <events :: molecule> :: alpha :: energy :: energy(const events :: molecule & event) : _event(event)
{}

// Getters

double report <events :: molecule> :: alpha :: energy :: before() const
{
  return 0.5 * ( (~this->_event.v1) * this->_event._alpha.molecule->mass() + this->_event.av1 * this->_event.av1 * this->_event._alpha.molecule->inertia_moment());
}

double report <events :: molecule> :: alpha :: energy :: after() const
{
  return this->_event._alpha.molecule->energy();
}

double report <events :: molecule> :: alpha :: energy :: delta() const
{
  return this->after() - this->before();
}

// Constructors

report <events :: molecule> :: alpha :: alpha(const events :: molecule & event) : velocity(event), momentum(event), angular_velocity(event), angular_momentum(event), energy(event), _event(event)
{}

// Getters

const size_t & report <events :: molecule> :: alpha :: id() const
{
  return this->_event._alpha.molecule->tag.id();
}

const size_t & report <events :: molecule> :: alpha :: atom() const
{
  return this->_event._alpha.atom;
}

const vec & report <events :: molecule> :: alpha :: position() const
{
  return this->_event._alpha.molecule->position();
}

const double & report <events :: molecule> :: alpha :: orientation() const
{
  return this->_event._alpha.molecule->orientation();
}

const double & report <events :: molecule> :: alpha :: mass() const
{
  return this->_event._alpha.molecule->mass();
}

// beta

// Public nested classes

// beta :: velocity

// Constructors

report <events :: molecule> :: beta :: velocity :: velocity(const events :: molecule & event) : _event(event)
{}

// Getters

const vec & report <events :: molecule> :: beta :: velocity :: before() const
{
  return this->_event.v2;
}

const vec & report <events :: molecule> :: beta :: velocity :: after() const
{
  return this->_event._beta.molecule->velocity();
}

vec report <events :: molecule> :: beta :: velocity :: delta() const
{
  return this->after() - this->before();
}

// beta :: momentum

// Constructors

report <events :: molecule> :: beta :: momentum :: momentum(const events :: molecule & event) : _event(event)
{}

// Getters

const vec & report <events :: molecule> :: beta :: momentum :: before() const
{
  return this->_event.p2;
}

vec report <events :: molecule> :: beta :: momentum :: after() const
{
  return this->_event._beta.molecule->velocity() * this->_event._beta.molecule->mass();
}

vec report <events :: molecule> :: beta :: momentum :: delta() const
{
  return this->after() - this->before();
}

// beta :: angular_velocity

// Constructors

report <events :: molecule> :: beta :: angular_velocity :: angular_velocity(const events :: molecule & event) : _event(event)
{}

// Getters

const double & report <events :: molecule> :: beta :: angular_velocity :: before() const
{
  return this->_event.av2;
}

const double & report <events :: molecule> :: beta :: angular_velocity :: after() const
{
  return this->_event._beta.molecule->angular_velocity();
}

double report <events :: molecule> :: beta :: angular_velocity :: delta() const
{
  return this->after() - this->before();
}

// beta :: angular_momentum

// Constructors

report <events :: molecule> :: beta :: angular_momentum :: angular_momentum(const events :: molecule & event) : _event(event)
{}

// Getters

const double & report <events :: molecule> :: beta :: angular_momentum :: before() const
{
  return this->_event.l2;
}

double report <events :: molecule> :: beta :: angular_momentum :: after() const
{
  return this->_event._beta.molecule->angular_velocity() * this->_event._beta.molecule->mass();
}

double report <events :: molecule> :: beta :: angular_momentum :: delta() const
{
  return this->after() - this->before();
}

// beta :: energy

// Constructors

report <events :: molecule> :: beta :: energy :: energy(const events :: molecule & event) : _event(event)
{}

// Getters

double report <events :: molecule> :: beta :: energy :: before() const
{
  return 0.5 * ((~this->_event.v2) * this->_event._beta.molecule->mass() + this->_event.av2 * this->_event.av2 * this->_event._beta.molecule->inertia_moment());
}

double report <events :: molecule> :: beta :: energy :: after() const
{
  return this->_event._beta.molecule->energy();
}

double report <events :: molecule> :: beta :: energy :: delta() const
{
  return this->after() - this->before();
}

// Constructors

report <events :: molecule> :: beta :: beta(const events :: molecule & event) : velocity(event), momentum(event), angular_velocity(event), angular_momentum(event), energy(event), _event(event)
{}

// Getters

const size_t & report <events :: molecule> :: beta :: id() const
{
  return this->_event._beta.molecule->tag.id();
}

const size_t & report <events :: molecule> :: beta :: atom() const
{
  return this->_event._beta.atom;
}

const vec & report <events :: molecule> :: beta :: position() const
{
  return this->_event._beta.molecule->position();
}

const double & report <events :: molecule> :: beta :: orientation() const
{
  return this->_event._beta.molecule->orientation();
}

const double & report <events :: molecule> :: beta :: mass() const
{
  return this->_event._beta.molecule->mass();
}

// Constructors

report <events :: molecule> :: report(const events :: molecule & event) : alpha(event), beta(event), _event(event)
{}

// Getters

const double & report <events :: molecule> :: time() const
{
  return this->_event._time;
}

const double & report <events :: molecule> :: module() const
{
  return this->_event.module;
}
