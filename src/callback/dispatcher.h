// Forward declarations

class dispatcher;

#if !defined(__forward__) && !defined(__nobb__callback__dispatcher__h)
#define __nobb__callback__dispatcher__h

// Libraries

#include <stdint.h>
#include <tuple>

// Includes

#include "callbacks/molecule.hpp"
#include "callbacks/bumper.hpp"
#include "data/hashtable.hpp"
#include "data/set.hpp"

class dispatcher
{
  // Nested enums

  enum type {all, stag, dtag};

  // Members

  struct
  {
    hashtable <size_t, type> types;
    hashtable <size_t, callback <events :: molecule> *> all;

    struct
    {
      hashtable <size_t, std :: tuple <callback <events :: molecule> *, uint8_t>> handles;
      set <callback <events :: molecule> *> map[255];
    } stag;

    struct
    {
      hashtable <size_t, std :: tuple <callback <events :: molecule> *, uint8_t, uint8_t>> handles;
      set <callback <events :: molecule> *> map[255][255];
    } dtag;
  } _molecule;

  struct
  {
    hashtable <size_t, callback <events :: bumper> *> all;
  } _bumper;

public:

  // Methods

  size_t add(callback <events :: molecule> *);
  size_t add(callback <events :: molecule> *, const uint8_t &);
  size_t add(callback <events :: molecule> *, const uint8_t &, const uint8_t &);

  size_t add(callback <events :: bumper> *);

  void trigger(const events :: molecule &);
  void trigger(const events :: bumper &);

  template <typename etype> void remove(const size_t &);

private:

  // Private static members

  static size_t autoincrement;
};

#endif
