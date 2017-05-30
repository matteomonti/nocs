#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <iomanip>

#include "engine/engine.hpp"
#include "molecule/molecule.h"
#include "graphics/window.h"


double rnd1()
{
  return ((double) rand()) / RAND_MAX - 0.5;
}

int main()
{
  srand(0);

  molecule alpha
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.1, 0.1},
    {rnd1(), rnd1()},
    0,
    M_PI
  );

  molecule beta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.2, 0.2},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule gamma
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.3, 0.3},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule delta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.4, 0.4},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule epsilon
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.5, 0.5},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  molecule zeta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.6, 0.6},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  engine engine(4);

  engine.add(alpha);
  engine.add(beta);
  engine.add(gamma);
  engine.add(delta);
  engine.add(epsilon);
  engine.add(zeta);

  window my_window;

  for(double t = 0; t <= 10; t += 0.1)
  {
    engine.run(t);

    my_window.clear();
    my_window.draw(engine);
    my_window.flush();

    usleep(1.e4);
  }

  window :: wait_click();

  molecule eta
  (
    {{{0, 0}, 1, 0.025}},
    {0.5, 0.5},
    {0., 0.},
    0.,
    0.
  );

  engine.add(eta);

  my_window.clear();
  my_window.draw(engine);
  my_window.flush();

  window :: wait_click();

  for(double t = 10; t <= 20; t += 0.1)
  {
    engine.run(t);

    my_window.clear();
    my_window.draw(engine);
    my_window.flush();

    usleep(1.e4);
  }

  for(size_t i = 1; i <= 6; i++)
  {
    window :: wait_click();

    engine.remove(i);

    my_window.clear();
    my_window.draw(engine);
    my_window.flush();

    window :: wait_click();

    for(double t = 10 + 10 * i; t < 20 + 10 * i || i == 6; t += 0.1)
    {
      engine.run(t);

      my_window.clear();
      my_window.draw(engine);
      my_window.flush();

      usleep(1.e4);
    }
  }
}

#endif
