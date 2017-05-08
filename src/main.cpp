#ifdef __main__

#include <iostream>
#include <unistd.h>

#include "event/events/molecule_molecule.h"
#include "event/events/bumper.h"
#include "event/events/grid.h"
#include "molecule/molecule.h"
#include "graphics/window.h"

int main()
{
  grid grid(9);

  molecule alpha
  (
    {{{0, 0}, 1, 0.05}, {{0.1, 0}, 1, 0.05}, {{0.2, 0}, 1, 0.05}, {{0.3, 0}, 1, 0.05}, {{0, 0.1}, 1, 0.05}, {{0, 0.2}, 1, 0.05}, {{0, 0.3}, 1, 0.05}},
    {0.1, 0.1},
    {-0.4, -0.2},
    0,
    M_PI
  );
  bumper beta
  (
    {0.98, 0.5},
    0.1
  );

  grid.add(alpha);
  grid.add(beta);

  window my_window("My pretty window!");

  for(double t = 0.;; t += 0.01)
  {
    alpha.integrate(t);

    my_window.clear();
    my_window.draw(alpha);
    my_window.draw(beta);
    my_window.flush();

    std :: cout << alpha.position() << ", " << beta.position() << std :: endl;
    std :: cout << "T: " << t << std :: endl;

    events :: grid my_event2(alpha, grid);
    if(my_event2.happens())
    {
      std :: cout << "Grid happens at: " << my_event2.time() << std :: endl;
      if(my_event2.time() < t + 0.01)
        my_event2.resolve();
    }


  for(int dx : {vec :: direct, vec :: left, vec :: right})
      for(int dy : {vec :: direct, vec :: up, vec :: down})
      {
        // TODO : Collision detection is perfect, but the module of the impulse (and therefore the resolution of the event), is not.
        events :: bumper my_event1(alpha, beta, dx | dy);

        if(my_event1.happens())
        {
          if(my_event1.time() < t + 0.01)
          {
              alpha.integrate(my_event1.time());
              my_window.clear();
              my_window.draw(alpha);
              my_window.draw(beta);
              my_window.flush();
              my_event1.resolve();
          }
        }

      }

    usleep(1e4);
std :: cout << "Energy of Molecule Alpha: " alpha.energy() << std :: endl << std :: endl;
  }

}
#endif
