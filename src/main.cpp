#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <iomanip>

#include "event/events/molecule.h"
#include "event/events/bumper.h"
#include "event/events/grid.h"
#include "molecule/molecule.h"
#include "data/heap.hpp"

int main()
{
  molecule beta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.806113, 0.962068},
    {0.226813, -0.569303},
    -3.28444,
    -0.687685
  );

  molecule delta
  (
    {{{0, 0}, 1, 0.025}, {{0.05, 0}, 1, 0.025}, {{0.1, 0}, 1, 0.025}, {{0.15, 0}, 1, 0.025}, {{0, 0.05}, 1, 0.025}, {{0, 0.1}, 1, 0.025}, {{0, 0.15}, 1, 0.025}},
    {0.787014, 0.833369},
    {-0.500274, 0.0212216},
    -1.09616,
    -3.03681
  );

  beta._time = 2.36874;
  delta._time = 2.36874;

  beta._version = 21;
  delta._version = 15;

  events :: molecule event(beta, vec :: direct, delta);

  if(event.happens())
  {
    std :: cout << std :: setprecision(10) << event << std :: endl;
  }
}

#endif
