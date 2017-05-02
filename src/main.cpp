#ifdef __main__

#include <iostream>
#include <unistd.h>

#include "event/events/molecule_molecule.h"
#include "molecule/molecule.h"
#include "graphics/window.h"

int main()
{
  molecule alpha
  (
    {{{0, 0}, 1, 0.05}, {{0.1, 0}, 1, 0.05}, {{0.2, 0}, 1, 0.05}, {{0.3, 0}, 1, 0.05}},
    {0.1, 0.1},
    {0.2, 0.2},
    0,
    -M_PI / 2
  );
  molecule beta
  (
    {{{0, 0}, 1, 0.05}, {{0.1, 0}, 1, 0.05}, {{0.2, 0}, 1, 0.05}, {{0.3, 0}, 1, 0.05}},
    {0.6, 0.8},
    {0.0, 0.0000001},
    M_PI / 2.,
    10. * M_PI
  );

  window my_window("My pretty window!");

  events :: molecule_molecule my_event(alpha, beta);

  my_window.draw(alpha);
  my_window.draw(beta);
  my_window.flush();
  window :: wait_click();

  for(double t = 0; t < my_event.time(); t += my_event.time() / 1000)
  {
    alpha.integrate(t);
    beta.integrate(t);

    my_window.clear();

    my_window.draw(beta);
    my_window.draw(alpha);

    my_window.flush();

    usleep(1e4);
  }

  window :: wait_click();
}

#endif
