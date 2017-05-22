#ifdef __main__

#include <iostream>
#include <unistd.h>

#include "event/events/molecule_molecule.h"
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

  events :: grid * event1 = new events :: grid (alpha, grid);
  events :: bumper * event2 = new events :: bumper (alpha, beta,0);
  events :: molecule_molecule * event3 = new events :: molecule_molecule(alpha,0, gamma);

  heap <event :: wrapper> heap;

  heap.push(event :: wrapper(event1));
  heap.push(event :: wrapper(event2));
  heap.push(event :: wrapper(event3));

  std :: cout << * (heap.peek()) << std :: endl;
  std :: cout << * (heap.pop()) << std :: endl;
  std :: cout << * (heap.peek()) << std :: endl;
  std :: cout << * (heap.pop()) << std :: endl;
  std :: cout << * (heap.peek()) << std :: endl;
  std :: cout << * (heap.pop()) << std :: endl;
}

#endif
