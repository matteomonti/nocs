#ifdef __main__

#include <iostream>
#include <unistd.h>

#include "engine/engine.hpp"
#include "molecule/molecule.h"

double rnd1()
{
  return ((double) rand()) / RAND_MAX - 0.5;
}

int main()
{
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
    {0.2, 0.3},
    {rnd1(), rnd1()},
    0,
    M_PI/4
  );

  engine engine(3);

  engine.add(alpha);
  engine.add(beta);

  engine.run(2);
}

#endif
