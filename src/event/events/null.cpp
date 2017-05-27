#include "null.h"

namespace events
{
  // Constructors

  null :: null()
  {
  }

  // Methods

  bool null :: current()
  {
    return false;
  }

  bool null :: resolve()
  {
    return false;
  }

  void null :: each(engine *, void (engine :: *)(molecule &))
  {
  }

  // Operators

  bool null :: operator == (const event &) const
  {
    return false;
  }
};
