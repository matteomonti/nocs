#include "engine.hpp"
#include "event/events/molecule.h"
#include "event/events/bumper.h"
#include "event/events/grid.h"

// tag

// Constructors

engine :: tag :: tag() : _id(autoincrement++), _references(0)
{
  memset(this->_tags, '\0', tags);
}

// Destructor

engine :: ~engine()
{
  delete [] this->_tags;
}

// Getters

const size_t & engine :: tag :: id() const
{
  return this->_id;
}

size_t engine :: tag :: size() const
{
  for(size_t i = 0; i < tags; i++)
    if(!(this->_tags[i]))
      return i;

  return tags;
}

const size_t & engine :: tag :: references() const
{
  return this->_references;
}

// Private methods

void engine :: tag :: add(const uint8_t & tag)
{
  for(size_t i = 0; i < tags; i++)
    if(!(this->_tags[i]))
    {
      this->_tags[i] = tag + 1;
      return;
    }
}

void engine :: tag :: remove(const uint8_t & tag)
{
  bool shift = false;

  for(size_t i = 0; i < tags; i++)
  {
    if(this->_tags[i] == tag + 1)
    {
      this->_tags[i] = 0;
      shift = true;
    }

    if(shift && i < tags - 1)
      this->_tags[i] = this->_tags[i + 1];
  }
}

// Operators

uint8_t engine :: tag :: operator [] (const size_t & index) const
{
  return this->_tags[index] - 1;
}

// Private operators

void engine :: tag :: operator ++ ()
{
  this->_references++;
}

void engine :: tag :: operator ++ (int)
{
  ++(*this);
}

void engine :: tag :: operator -- ()
{
  this->_references--;
}

void engine :: tag :: operator -- (int)
{
  --(*this);
}

// Private static members

size_t engine :: tag :: autoincrement = 1;

// engine

// Constructors

engine :: engine(const size_t & fineness) : _time(0), _grid(fineness), _tags(new hashtable <size_t, molecule *> [256]), reset(*this)
{
  this->_elasticity.all = 1.;

  for(size_t i = 0; i < 255; i++)
  {
    this->_elasticity.stag[i] = -1;

    for(size_t j = 0; j < 255; j++)
      this->_elasticity.dtag[i][j] = -1;
  }
}

// Getters

const size_t & engine :: fineness() const
{
  return this->_grid.fineness();
}

// Setters

void engine :: elasticity(const double & elasticity)
{
  assert(elasticity > 0);
  this->_elasticity.all = elasticity;

  this->_molecules.each([&](molecule * molecule)
  {
    this->refresh(*molecule);
  });
}

void engine :: elasticity(const uint8_t & tag, const double & elasticity)
{
  assert(elasticity > 0);
  this->_elasticity.stag[tag] = elasticity;

  this->_molecules.each([&](molecule * molecule)
  {
    this->refresh(*molecule);
  });
}

void engine :: elasticity(const uint8_t & alpha, const uint8_t & beta, const double & elasticity)
{
  assert(elasticity > 0);
  this->_elasticity.dtag[alpha][beta] = elasticity;
  this->_elasticity.dtag[beta][alpha] = elasticity;

  this->_molecules.each([&](molecule * molecule)
  {
    this->refresh(*molecule);
  });
}

// Methods

size_t engine :: add(const molecule & molecule)
{
  class molecule * entry = new class molecule(molecule);
  this->_molecules.add(entry->tag.id(), entry);

  this->_grid.add(*entry);
  this->refresh(*entry);

  return entry->tag.id();
}

void engine :: add(const bumper & bumper)
{
  class bumper * entry = new class bumper(bumper);
  this->_bumpers.add(entry);

  this->_grid.add(*entry);

  for(ssize_t dx = -1; dx <= 1; dx++)
    for(ssize_t dy = -1; dy <= 1; dy++)
    {
      ssize_t x = (bumper.mark.x() + this->_grid.fineness() + dx) % this->_grid.fineness();
      ssize_t y = (bumper.mark.y() + this->_grid.fineness() + dy) % this->_grid.fineness();

      this->_grid.each <class molecule> (x, y, [&](class molecule & molecule)
      {
        this->refresh(molecule);
      });
    }
}

void engine :: remove(const size_t & id)
{
  molecule * entry = this->_molecules[id];
  this->_grid.remove(*entry);
  entry->disable();

  this->_molecules.remove(id);
  this->_garbage.add(entry);
}

void engine :: tag(const size_t & id, const uint8_t & tag)
{
  molecule * entry = this->_molecules[id];
  entry->tag.add(tag);
  this->_tags[tag].add(id, entry);
}

void engine :: untag(const size_t & id, const uint8_t & tag)
{
  molecule * entry = this->_molecules[id];
  entry->tag.remove(tag);
  this->_tags[tag].remove(id);
}

void engine :: run(const double & time)
{
  while(this->_events.size() && ((const event *) (this->_events.peek()))->time() <= time)
  {
    event * event = this->_events.pop();
    event->each(this, &engine :: decref);

    if(event->resolve())
    {
      event->each(this, &engine :: refresh);
      event->callback(this->_dispatcher);
    }

    delete event;
  }

  if(time > this->_time)
    this->_time = time;

  this->collect();
}

// Private methods

double engine :: elasticity(const molecule & alpha, const molecule & beta)
{
  if(alpha.tag.size() == 1 && beta.tag.size() == 1 && this->_elasticity.dtag[alpha.tag[0]][beta.tag[0]] > 0)
    return this->_elasticity.dtag[alpha.tag[0]][beta.tag[0]];
  else if(alpha.tag.size() == 1 && beta.tag.size() == 0 && this->_elasticity.stag[alpha.tag[0]] > 0)
    return this->_elasticity.stag[alpha.tag[0]];
  else if(alpha.tag.size() == 0 && beta.tag.size() == 1 && this->_elasticity.stag[beta.tag[0]] > 0)
    return this->_elasticity.stag[beta.tag[0]];
  else
    return this->_elasticity.all;
}

void engine :: refresh(molecule & molecule, const size_t & skip)
{
  // Grid event

  events :: grid * event = new events :: grid(molecule, this->_grid);

  if(event->happens())
  {
    event->each(this, &engine :: incref);
    this->_events.push(event :: wrapper(event));
  }
  else
    delete event;

  for(ssize_t dx = -1; dx <= 1; dx++)
    for(ssize_t dy = -1; dy <= 1; dy++)
    {
      ssize_t x = molecule.mark.x() + dx;
      ssize_t y = molecule.mark.y() + dy;

      int fold = vec :: direct;

      if(x < 0)
        fold |= vec :: right;
      else if(x >= this->_grid.fineness())
        fold |= vec :: left;

      if(y < 0)
        fold |= vec :: up;
      else if(y >= this->_grid.fineness())
        fold |= vec :: down;

      x = (x + this->_grid.fineness()) % this->_grid.fineness();
      y = (y + this->_grid.fineness()) % this->_grid.fineness();

      // Molecule event

      this->_grid.each <class molecule> (x, y, [&](class molecule & beta)
      {
        if(beta.tag.id() == molecule.tag.id() || beta.tag.id() == skip)
          return;

        events :: molecule * event = new events :: molecule(molecule, fold, beta, this->elasticity(molecule, beta));

        if(event->happens())
        {
          event->each(this, &engine :: incref);
          this->_events.push(event);
        }
        else
          delete event;
      });

      // Bumper event

      this->_grid.each <bumper> (x, y, [&](bumper & bumper)
      {
        events :: bumper * event = new events :: bumper(molecule, fold, bumper);

        if(event->happens())
        {
          event->each(this, &engine :: incref);
          this->_events.push(event);
        }
        else
          delete event;
      });
    }
}

void engine :: incref(molecule & molecule, const size_t &)
{
  molecule.tag++;
}

void engine :: decref(molecule & molecule, const size_t &)
{
  molecule.tag--;
}

void engine :: collect()
{
  set <molecule *> old;

  this->_garbage.each([&](molecule * entry)
  {
    if(!(entry->tag.references()))
      old.add(entry);
  });

  old.each([&](molecule * entry)
  {
    this->_garbage.remove(entry);
    delete entry;
  });
}
