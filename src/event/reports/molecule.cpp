#include "molecule.h"
#include "event/events/molecule.h"

namespace reports
{
  // Constructors

  molecule :: molecule(const events :: molecule & event) : _event(event)
  {
  }

  // Getters

  const size_t & molecule :: alpha() const
  {
    return this->_event._alpha.molecule->tag.id();
  }

  const size_t & molecule :: beta() const
  {
    return this->_event._beta.molecule->tag.id();
  }
};
