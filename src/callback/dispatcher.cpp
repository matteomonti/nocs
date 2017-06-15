#include "dispatcher.h"

// Methods

size_t dispatcher :: add(callback <events :: molecule> * event)
{
  size_t id = autoincrement++;
  this->_molecule.add(id, event);

  return id;
}

size_t dispatcher :: add(callback <events :: bumper> * event)
{
  size_t id = autoincrement++;
  this->_bumper.add(id, event);

  return id;
}

void dispatcher :: trigger(const events :: molecule & event)
{
  this->_molecule.each([&](callback <events :: molecule> * callback)
  {
    callback->trigger(event);
  });
}

void dispatcher :: trigger(const events :: bumper & event)
{
  this->_bumper.each([&](callback <events :: bumper> * callback)
  {
    callback->trigger(event);
  });
}

template <> void dispatcher :: remove <events :: molecule> (const size_t & id)
{
  this->_molecule.remove(id);
}

template <> void dispatcher :: remove <events :: bumper> (const size_t & id)
{
  this->_bumper.remove(id);
}

// Private static members

size_t dispatcher :: autoincrement;
