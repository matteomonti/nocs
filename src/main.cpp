#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <iomanip>

#include "engine/engine.hpp"
#include "molecule/molecule.h"
#include "elements/bumper.h"
#include "graphics/window.h"

double rnd1()
{
  return ((double) rand()) / RAND_MAX - 0.5;
}

int main()
{
  srand(0);

  engine engine(80);

  for(double x = 0.01; x < 1.; x += 0.01)
    for(double y = 0.01; y < 1.; y += 0.01)
    {
      molecule molecule
      (
        {{{0, 0}, 1, 0.0025}},
        {x, y},
        {rnd1(), rnd1()},
        0,
        M_PI/4
      );

      engine.add(molecule);
    }

  window my_window;

  for(double t = 0;; t += 0.03)
  {
    engine.run(t);

    my_window.clear();
    my_window.draw(engine);
    my_window.flush();

    usleep(1.e4);
  }
}

#endif
