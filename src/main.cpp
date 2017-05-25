#ifdef __main__

#include <iostream>
#include <unistd.h>

#include "engine/grid.hpp"
#include "event/events/molecule.h"
#include "event/events/bumper.h"
#include "event/events/grid.h"
#include "molecule/molecule.h"
#include "data/heap.hpp"

int main()
{
  grid grid(9);

  molecule alpha
  (
    {{{0, 0}, 1, 0.05}, {{0.1, 0}, 1, 0.05}, {{0.2, 0}, 1, 0.05}, {{0.3, 0}, 1, 0.05}, {{0, 0.1}, 1, 0.05}, {{0, 0.2}, 1, 0.05}, {{0, 0.3}, 1, 0.05}},
    {0.1, 0.1},
    {0.4, 0.2},
    0,
    M_PI
  );

  molecule gamma
  (
    {{{0, 0}, 1, 0.05}, {{0.1, 0}, 1, 0.05}, {{0.2, 0}, 1, 0.05}, {{0.3, 0}, 1, 0.05}, {{0, 0.1}, 1, 0.05}, {{0, 0.2}, 1, 0.05}, {{0, 0.3}, 1, 0.05}},
    {0.8, 0.8},
    {-0.4, -0.2},
    0,
    -M_PI
  );

  bumper beta
  (
    {0.5, 0.5},
    0.1
  );

  grid.add(alpha);
  grid.add(beta);

  grid.each <molecule> (0, 0, [](molecule & molecule)
  {
    std :: cout << molecule;
    std :: cout << std :: endl;
  });
}

#endif
