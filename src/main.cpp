#ifdef __main__

#include <iostream>

#include "event/events/molecule_molecule.h"

int main()
{
  molecule alpha({{{0, 0}, 1, 1}, {{2, 0}, 1, 1}, {{4, 0}, 1, 1}, {{6, 0}, 1, 1}}, {5, 10}, {0, -2});
  molecule beta({{{0, 0}, 1, 1}, {{2, 0}, 1, 1}, {{4, 0}, 1, 1}, {{6, 0}, 1, 1}}, {7, 2}, {0, 1});

  std :: cout << "Alpha radius: " << alpha.radius() << std :: endl;
  std :: cout << "Beta radius: " << beta.radius() << std :: endl;

  events :: molecule_molecule(alpha, beta);
}

#endif
