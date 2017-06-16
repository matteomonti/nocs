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

enum {small, big};

int main()
{
  srand(0);

  engine engine(8);

  for(double x = 0.1; x < 1.; x += 0.1)
    for(double y = 0.1; y < 0.8; y += 0.1)
    {
      std :: cout << x << ", " << y << std :: endl << std :: flush;
      molecule molecule
      (
        {{{0, 0}, 1, 0.025}},
        {x, y},
        {rnd1(), rnd1()},
        0,
        M_PI/4
      );

      engine.tag(engine.add(molecule), small);
    }

  for(double x = 0.2; x < 1.; x += 0.2)
    {
      molecule molecule
      (
        {{{0, 0}, 1, 0.05}},
        {x, 0.9},
        {rnd1(), rnd1()},
        0,
        M_PI/4
      );

      engine.tag(engine.add(molecule), big);
    }

  window my_window;

  my_window.draw(engine);
  window :: wait_click();

  engine.elasticity(big, big, 0.4);

  for(double t = 0;; t += 1.)
  {
    engine.reset.energy.tag(small, 10.);

    for(double dt = 0.; dt < 1.; dt += 0.03)
    {
      engine.run(t + dt);

      double energy = 0;
      engine.each <molecule> ([&](const molecule & molecule)
      {
        energy += molecule.energy();
      });

      std :: cout << energy << std :: endl;

      my_window.clear();
      my_window.draw(engine);
      my_window.flush();

      usleep(1.e4);
    }
  }
}

#endif
