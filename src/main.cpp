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
    {{{0, 0}, 1, 0.05}, {{0.1, 0}, 1, 0.05}, {{0.2, 0}, 1, 0.05}, {{0.3, 0}, 1, 0.05}, {{0, 0.1}, 1, 0.05}, {{0, 0.2}, 1, 0.05}, {{0, 0.3}, 1, 0.05}},
    {0.56, 0.1},
    {0.0, -0.5},
    0,
    M_PI
  );
  molecule beta
  (
    {{{0, 0}, 1, 0.05}, {{0.1, 0}, 1, 0.05}, {{0.2, 0}, 1, 0.05}, {{0.3, 0}, 1, 0.05}},
    {0.6, 0.7},
    {0.0, 0.0000001},
    M_PI / 2.,
    -(M_PI * 10)
  );

  window my_window("My pretty window!");

  while(true)
  {
    alpha.integrate(0.001);
    beta.integrate(0.001);

    if(alpha._position.x > 1.)
      alpha._position.x -= 1.;

    if(alpha._position.x < 0.)
      alpha._position.x += 1.;

    if(alpha._position.y > 1.)
      alpha._position.y -= 1.;

    if(alpha._position.y < 0.)
      alpha._position.y += 1.;

    if(beta._position.x > 1.)
      beta._position.x -= 1.;

    if(beta._position.x < 0.)
      beta._position.x += 1.;

    if(beta._position.y > 1.)
      beta._position.y -= 1.;

    if(beta._position.y < 0.)
      beta._position.y += 1.;

    my_window.clear();
    my_window.draw(alpha);
    my_window.draw(beta);
    my_window.flush();

    std :: cout << alpha.position() << ", " << beta.position() << std :: endl;

    for(int dx : {vec :: direct, vec :: left, vec :: right})
      for(int dy : {vec :: direct, vec :: up, vec :: down})
      {
        events :: molecule_molecule my_event(alpha, dx | dy, beta);
        if(my_event.happens())
        {
          std :: cout << "EVENT HAPPENS AT " << my_event.time() << std :: endl;

          if(my_event.time() < 0.001)
            my_event.resolve();
        }
      }

    alpha._time = 0.;
    beta._time = 0.;
    usleep(1e4);
  }
}

#endif
