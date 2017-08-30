// Forward declarations

class window;

#if !defined(__forward__) && !defined(__nobb__graphics__window__h)
#define __nobb__graphics__window__h

// Libraries

#include "lockpick.h"

// Includes

#include "molecule/atom.h"
#include "engine/engine.hpp"
#include "molecule/molecule.h"
#include "elements/bumper.h"

class window : public lockpick :: window
{
public:

  // Constructors

  window(const char * = nullptr, int = __default_width, int = __default_height, int = 0, int = 0, lockpick :: color = lockpick :: color(255, 255, 255), int = 95, int = 95);

  // Methods

  void draw(const engine &);
  void draw_with_grid(const engine &);
  void draw(const engine &, const uint8_t &);
  void draw(const molecule &);
  void draw(const bumper &);

private:

  // Private methods

  void grid(const engine &);
};

#endif
