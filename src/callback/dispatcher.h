// Forward declarations

class dispatcher;

#if !defined(__forward__) && !defined(__nobb__callback__dispatcher__h)
#define __nobb__callback__dispatcher__h

// Includes

#include "callbacks/molecule.hpp"
#include "data/hashtable.hpp"

class dispatcher
{
  // Members

  hashtable <size_t, callback <events :: molecule> *> _molecule;

public:

  // Methods

  size_t add(callback <events :: molecule> *);
  void trigger(const events :: molecule &);
  template <typename etype> void remove(const size_t &);

private:

  // Private static members

  static size_t autoincrement;
};

#endif
