#ifdef __main__

#include <iostream>

#include "event/events/molecule_molecule.h"

int main()
{
  molecule alpha({{{0, 0}, 1, 1}, {{2, 0}, 1, 1}, {{4, 0}, 1, 1}, {{6, 0}, 1, 1}}, {0, 0}, {0, 0}, 0, - M_PI * 2.);
  molecule beta({{{0, 0}, 1, 1}, {{2, 0}, 1, 1}, {{4, 0}, 1, 1}, {{6, 0}, 1, 1}}, {2, 6}, {0, 0.0001}, M_PI / 2.);

  events :: molecule_molecule(alpha, beta);
}

#endif
